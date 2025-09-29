#include <stdio.h>
#include <string.h>
#include "../includes/cities.h"
#include "../includes/utils.h"
#include "../includes/meteo.h"
#include "../includes/city.h"
#include "../includes/cache.h"
#include "../includes/parsedata.h"

/*-------------Internal function definitions----------------*/


/*--------------------------------------------------------*/


int city_init(char* _Name, double _Latitude, double _Longitude, City** _CityPtr) {
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

int city_get_info(Cities* _Cities) {
    
  char* user_input = NULL;
  if (utils_get_user_input(&user_input) != 0) {
    free(user_input);
    printf("Please try again\n");
    }

  City* user_city = NULL;

  if (cities_get(_Cities, user_input, &user_city) != 0) {
    printf("Failed to get city\n");
    printf("Would you like to try to add it from API? Y/N: ");
    if (utils_continue() != 0) {
      free(user_input);
      return -1;
    } else {
      
    if (city_add_from_api(user_input, _Cities) != 0) {
      return -1;
    }
    }
    
    if (cities_get(_Cities, user_input, &user_city) != 0) {
      return -1;
    }
    
    printf("%f | %f | %s \n", user_city->latitude, user_city->longitude, user_city->name);

  }

  meteo_get_weather_data(user_city->latitude, user_city->longitude, user_city->name);
  
  free(user_city);
  free(user_input);
  user_input = NULL;

  return 0;
}


int city_add_from_api(char* _CityName, Cities* _Cities) {
  if (_CityName == NULL) {
    return -1;
  }

  cJSON* root = NULL;
  root = meteo_get_city_data(_CityName);
  if (root == NULL) {
    printf("Failed to get city data from API\n");
    return -1;
  }

  double latitude, longitude = 0.0f;
  char name[50];
  cJSON* item = NULL;

  if (cJSON_IsArray(root) && cJSON_GetArraySize(root) > 0) {
      item = cJSON_GetArrayItem(root, 0);
  }

  if (cJSON_IsArray(root)) {
      item = cJSON_GetArrayItem(root, 0);
  }
  if (!item && cJSON_IsObject(root)) {
      cJSON *results = cJSON_GetObjectItemCaseSensitive(root, "results");
      if (cJSON_IsArray(results)) {
          item = cJSON_GetArrayItem(results, 0);
      }
  }

  strcpy(name, parsedata_get_string(item, "name"));
  latitude = parsedata_get_double(item, "latitude");
  longitude = parsedata_get_double(item, "longitude");
  if (latitude == 0.0f && longitude == 0.0f) {
  
    printf("Received empty data\n");
    return -1;
  }

  if (cities_add(_Cities, name, latitude, longitude, NULL) != 0) {
    return -1;
  }

  cJSON_Delete(root);

  return 0;

}
