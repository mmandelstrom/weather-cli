#include <stdio.h>
#include <string.h>
#include "../includes/linkedlist.h"
#include "../includes/utils.h"
#include "../includes/meteo.h"
#include "../includes/city.h"
#include "../includes/cache.h"
#include "../includes/parsedata.h"

/*-------------Internal function definitions----------------*/


/*--------------------------------------------------------*/


int city_Init(char* _Name, double _Latitude, double _Longitude, City** _CityPtr) {
	if(_Name == NULL || _CityPtr == NULL) {
   return -1; 
  }

	City* _City = (City*)malloc(sizeof(City));
	if(_City == NULL) {
		printf("Failed to allocate memory for new City\n");
		return -1;
	}

	memset(_City, 0, sizeof(City));

	_City->name = utils_strdup(_Name);
	if(_City->name == NULL) {
		printf("Failed to allocate memory for City name\n");
		free(_City);
		return -1;
	}

  _City->latitude = _Latitude;
  _City->longitude = _Longitude;
  _City->next = NULL;
  _City->prev = NULL;


  char* json_str;
  char* hashed_name;
  char filepath[50];
  sprintf(filepath, "%s%f%f", _Name, _Latitude, _Longitude);
  hashed_name = utils_hash_url(filepath);


  cJSON* root = cJSON_CreateObject();
  if (root == NULL) {
    perror("cJSON_CreateObject");
    return -1;
  }
  
  cJSON_AddStringToObject(root, "name", _Name);
  cJSON_AddNumberToObject(root, "latitude", _Latitude);
  cJSON_AddNumberToObject(root, "longitude", _Longitude);

  json_str = cJSON_PrintUnformatted(root);

  if (cache_create_file(hashed_name, json_str, CITY_CACHE) != 0) {
    return -1;
  }
  
  *(_CityPtr) = _City;
  free(hashed_name);
  cJSON_Delete(root);
  cJSON_free(json_str);
	
	return 0;
}








int city_get_info(Cities* _CityList) {
    
  char* user_input = NULL;
  if (utils_get_user_input(&user_input) != 0) {
    free(user_input);
    printf("Please try again\n");
    }

  City* user_city = NULL;

  if (cities_get(_CityList, user_input, &user_city) != 0) {
    printf("Failed to get city\n");
    free(user_input);
    return -1;
  }

  printf("user_city: %s\n", user_city->name);

  meteo_get_city_data(user_city->latitude, user_city->longitude, user_city->name);
  
  free(user_city);
  free(user_input);
  user_input = NULL;

  return 0;
}
