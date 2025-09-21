#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "../includes/utils.h"
#include "../includes/cities.h"
#include "../includes/http.h"

//-------------Internal function definitions----------------

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

int cities_parse_list(Cities* _Cities, const char* list);

//--------------------------------------------------------



int cities_init(Cities* _Cities) {

  memset(_Cities, 0, sizeof(*_Cities));

  if (cities_parse_list(_Cities, cities_list) != 0) {
    return -1;
  }
  cities_print(_Cities);
  
  char* user_input = NULL;

  while (1) {
    if (get_user_input(&user_input) != 0) {
      free(user_input);
      printf("Please try again\n");
      continue;
      }

    City* user_city = NULL;

    if (cities_get(_Cities, user_input, &user_city) != 0) {
      printf("Failed to get city\n");
      free(user_input);
      return -1;
    }

    free(user_input);
    user_input = NULL;

    printf("user_city: %s\n", user_city->name);

    meteo_get_city_data(user_city);

    if (break_loop() != 0) {
      break;
    }
  }
 
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

int cities_parse_list(Cities* _Cities, const char* list) {
  char* list_copy = my_strdup(list);
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

int cities_add(Cities* _Cities, char* _Name, float _Latitude, float _Longitude, City** _City) {
  City* new_city = (City*)malloc(sizeof(City));
  if (new_city == NULL) {
    printf("Unable to allocate memory for City: %s\n", _Name);
    return -1;
  }

  new_city->name = _Name;
  new_city->latitude = _Latitude;
  new_city->longitude = _Longitude;
  new_city->next = NULL;
  new_city->prev = NULL;
  
  //If there is no tail the list is empty
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
  
  /*------------------DEBUG-------------------
	printf("_Cities->head: %s\n", _Cities->head->name);
	printf("_City->name: %s\n", _City->name);
	------------------------------------------*/
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
      printf("City %s found\n", current->name);
      if (_CityPtr != NULL) {
        *_CityPtr = current;
        return 0;
      }
    }
    current = current->next;
  }
   return -1;
}
void cities_dispose(Cities* c);
