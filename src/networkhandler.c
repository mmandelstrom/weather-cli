#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/networkhandler.h"
#include "../includes/cache.h"
#include "../includes/utils.h"
#include "../includes/http.h"


int networkhandler_get_data(char* _URL, Meteo** _Meteo) {
  if (_Meteo == NULL) {
    return -1;
  }

  *(_Meteo) = NULL;

  NetworkHandler nh; /*Struct för att ta emot data från fil eller api*/
  networkhandler_init(&nh);

  char* filename;
  Meteo* mt = calloc(1, sizeof *mt);
  int returncode = -1;
  
  do {
    if (mt == NULL) {
      fprintf(stderr, "Unable to allocate memory for Meteo\n");
      break;
    }
    
    filename = utils_hash_url(_URL);

    if (filename &&
    cache_check_file(filename) == 0 &&
    compare_time(filename, 900) == 0) {
      printf("Reading from file: %s\n", filename);
      if (cache_read_file(filename, &nh) != 0) {
        fprintf(stderr, "Failed to read file: %s\n", filename);
        break;
      }
    } else {
      printf("Making APIRequest\n");
      if (http_api_request(_URL, &nh) != 0) {
                fprintf(stderr, "Failed to make api request with url: %s\n", _URL);
        break;
      }
    }
    
    if (nh.data == NULL || nh.size == 0) {
      fprintf(stderr, "Data is empty\n");
      break;
    }

    mt->data = (char*)malloc(nh.size + 1);
    if (mt->data == NULL) {
      fprintf(stderr, "Failed to allocate memory for Meteo data\n");
      break;
    }
    
    memcpy(mt->data, nh.data, nh.size);
    mt->size = nh.size;
    *(_Meteo) = mt;
    returncode = 0;

  } while(0);
  
  free(filename); 
  networkhandler_destroy(&nh);
  
  if (returncode != 0) {
    if (mt != NULL) {
    free(mt->data);
    free(mt);
    }
  }

  return returncode;
}

int networkhandler_init(NetworkHandler* _Nh) {
   if (_Nh == NULL) {
        return -1;
    }
    _Nh->data = NULL;
    _Nh->size = 0;
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
