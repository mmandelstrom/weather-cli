#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/networkhandler.h"
#include "../includes/cache.h"
#include "../includes/utils.h"
#include "../includes/http.h"

/*------------------Internal function definitons------------------*/
void Networkhandler_cleanup();

/*---------------------------------------------------------------*/
int networkhandler_get_data(char* _URL, Meteo** _Meteo) {
  if (_Meteo == NULL) {
    return -1;
  }

  *(_Meteo) = NULL;

  char* filename = utils_hash_url(_URL);
  Meteo* mt = calloc(1, sizeof *mt);
 
  if (mt == NULL) {
    fprintf(stderr, "Unable to allocate memory for Meteo\n");
    return -1;
  }

  NetworkHandler* nh = {0}; /*Struct för att ta emot data från fil eller api*/

  if (filename &&
  cache_check_file(filename, WEATHER_DATA_CACHE) == 0 &&
  utils_compare_time(filename, WEATHER_DATA_CACHE, 900) == 0) {
    printf("Reading from file: %s\n", filename);
    if (cache_read_file(filename, &nh, WEATHER_DATA_CACHE) != 0) {
      fprintf(stderr, "Failed to read file: %s\n", filename);
      Networkhandler_cleanup(nh, filename, mt);
      return -1;
    }
  } else {
    printf("Making APIRequest\n");
    if (http_api_request(_URL, &nh) != 0) {
      fprintf(stderr, "Failed to make api request with url: %s\n", _URL);
      Networkhandler_cleanup(nh, filename, mt);
      return -1;
    }
    if (cache_create_file(filename, nh->data, WEATHER_DATA_CACHE) != 0) {
      printf("Failed to create cache file\n");
    }
  }
    
  if (nh->data == NULL || nh->size == 0) {
    fprintf(stderr, "Data is empty\n");
    Networkhandler_cleanup(nh, filename, mt);
    return -1;
  }

  mt->data = (char*)malloc(nh->size + 1);
  if (mt->data == NULL) {
    fprintf(stderr, "Failed to allocate memory for Meteo data\n");
    Networkhandler_cleanup(nh, filename, mt);
    return -1;
  }
  
  memcpy(mt->data, nh->data, nh->size);
  mt->size = nh->size;
  *(_Meteo) = mt;

  return 0;
}

int networkhandler_destroy(NetworkHandler* _Nh){
  if (!_Nh) {
    return -1;
  }

  free(_Nh->data);
  _Nh->data = NULL;
  _Nh->size = 0;

  return 0;
}

void Networkhandler_cleanup(NetworkHandler* _Nh, char* _Filename, Meteo* _Meteo) {
  if (_Meteo != NULL) {
    free(_Meteo->data);
    free(_Meteo);
  }
  networkhandler_destroy(_Nh);
  free(_Filename);
}
