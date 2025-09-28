#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/utils.h"
#include "../includes/linkedlist.h"
#include "../includes/city.h"
#include "../includes/tinydir.h"
#include "../includes/cache.h"
#include "../includes/networkhandler.h"
#include "../includes/parsedata.h"
#include <stdbool.h>

/*--------Internal function definitions-------*/
void cities_print(Cities* _cities);
int cities_add_from_string(Cities* _Cities, const char* list);
void Cities_AddFromFiles(Cities* _Cities);

const char* cities_list = "Stockholm:59.3293:18.0686\n"
  "Göteborg:57.7089:11.9746\n"
  "Malmö:55.6050:13.0038\n"
  "Uppsala:59.8586:17.6389\n"
  "Västerås:59.6099:16.5448\n"
  "Örebro:59.2741:15.2066\n"
  "Linköping:58.4109:15.6216\n"
  "Helsingborg:56.0465:12.6945\n"
  "Jönköping:57.7815:14.1562\n"
  "Norrköping:58.5877:16.1924\n"
  "Lund:55.7047:13.1910\n"
  "Gävle:60.6749:17.1413\n"
  "Sundsvall:62.3908:17.3069\n"
  "Umeå:63.8258:20.2630\n"
  "Luleå:65.5848:22.1567\n"
  "Kiruna:67.8558:20.2253\n";


/*--------------------------------------------*/
int cities_init(Cities* _Cities) {

  memset(_Cities, 0, sizeof(*_Cities));

  utils_create_folder(WEATHER_DATA_CACHE);
  utils_create_folder(CITY_CACHE);
  Cities_AddFromFiles(_Cities);

  if (cities_add_from_string(_Cities, cities_list) != 0) {
    return -1;
  }
  
  cities_print(_Cities);

  city_get_info(_Cities);
  
  return 0;
}

int cities_add_from_string(Cities* _Cities, const char* list) {
  char* list_copy = utils_strdup(list);
  if (list_copy == NULL) {
    printf("Failed to allocate memory for list\n");
    return -1;
  }

  char* ptr = list_copy;
  char* name = NULL;
  char* lat_str = NULL;
  char* lon_str = NULL;
 
  	do {
		if(name == NULL) {
			name = ptr;
		}
		else if(lat_str == NULL) {
			if(*(ptr) == ':') {
				lat_str = ptr + 1;
				*(ptr) = '\0';
			}
		}
		else if(lon_str == NULL) {
			if(*(ptr) == ':') {
				lon_str = ptr + 1;
				*(ptr) = '\0';
			}
		}
		else {
			if(*(ptr) == '\n') {
				*(ptr) = '\0';

				cities_add(_Cities, name, atof(lat_str), atof(lon_str), NULL);

				name = NULL;
				lat_str = NULL;
				lon_str = NULL;
			}
		}

		ptr++;

	} while (*(ptr) != '\0');



    return 0;
}

void cities_print(Cities* _Cities) {
  if (_Cities->head == NULL) {
    printf("List is empty, no cities to print\n");
  } else {
    City* current = _Cities->head;

    do {
      printf("- %s\n", current->name);
      current = current->next;
    } while (current != NULL);
  }
}

int cities_add(Cities* _Cities, char* _Name, float _Latitude, float _Longitude, City** _City) {
  if(_Cities == NULL || _Name == NULL) {
    return -1;
  }
 
  City* existing = NULL;
  if (cities_get(_Cities, _Name, &existing) == 0) {
    if (_City != NULL) {
      *(_City) = existing;
    }
    return 1;
  }

	int result = 0;
	City* new_city = NULL;
	
	result = city_Init(_Name, _Latitude, _Longitude, &new_city);

  if(result != 0) {
		printf("Failed to initialize City struct! Errorcode: %i\n", result);
		return -1;
	}
    
  if (_Cities->tail == NULL) {
    _Cities->head = new_city;
    _Cities->tail = new_city;
  } else {
    new_city->prev = _Cities->tail;
    _Cities->tail->next = new_city;
    _Cities->tail = new_city;
  }

  if (_City != NULL) {
    *(_City) = new_city;
  }

  return 0;
}


void cities_remove(Cities* _Cities, City* _City) {
  
	if (_City->next == NULL && _City->prev == NULL) {
		_Cities->tail = NULL;
        _Cities->head = NULL;
    } else if (_City == _Cities->tail) {
		_Cities->tail = _City->prev;
        _City->prev->next = NULL;
    } else if (_City == _Cities->head){
		_Cities->head = _City->next;
        _City->next->prev = NULL;
    } else {
        _City->next->prev = _City->prev;
        _City->prev->next = _City->next;
    }
    
	free(_City);

  return;
}

int cities_get(Cities* _Cities, char* _Name, City** _CityPtr) {
  City* current = _Cities->head;

  while(current != NULL) {
    if (current->name && strcmp(current->name, _Name) == 0) {
      if (_CityPtr != NULL) {
        *_CityPtr = current;
        return 0;
      }
    }
    current = current->next;
  }
   return -1;
}

void Cities_AddFromFiles(Cities* _Cities) {
  if (_Cities == NULL) {
      return;
  }
  NetworkHandler* nh = {0};

  tinydir_dir dir;
  tinydir_open(&dir, CITY_CACHE);

  while (dir.has_next) {
    tinydir_file file;
    tinydir_readfile(&dir, &file);

    if (!file.is_dir) {
      char filename[50];
      strcpy(filename, file.name);
      filename[strlen(filename) - 5] = '\0';
      char *dot = strrchr(filename, '.');
      if (dot && strcmp(dot, ".json") == 0) {
        *dot = '\0'; /*Remove .json*/
      }

      if (cache_read_file(filename, &nh, CITY_CACHE) != 0) {
        return;
      }

      cJSON* root = cJSON_Parse(nh->data); 
      if (root == NULL) {
      const char* error_pointer = cJSON_GetErrorPtr();
      if (error_pointer != NULL){
        fprintf(stderr,"JSON error %s\n", error_pointer);
        }
        return;
      }
      char name[50];
      strcpy(name, parsedata_get_string(root, "name"));
      double lat = parsedata_get_double(root, "latitude");
      double lon = parsedata_get_double(root, "longitude");
      cities_add(_Cities, name, lat, lon, NULL);
      
      cJSON_Delete(root);
    }

    tinydir_next(&dir);
  }

  tinydir_close(&dir);
}

