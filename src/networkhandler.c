#include <stdio.h>
#include <string.h>
#include "../includes/networkhandler.h"
#include "../includes/cache.h"
#include "../includes/utils.h"
#include "../includes/http.h"


int networkhandler_get_data(char* _URL, Meteo** _Meteo) {
  NetworkHandler* nh = {0}; /*Struct för att ta emot data från fil eller api*/
  Meteo* mt = calloc(1, sizeof *mt);
  if (mt == NULL) {
    printf("Failed to allocate memory for Meteo struct\n");
    return -1;
  }

  char* filename = utils_hash_url(_URL);

  printf("Hashed: %s\n", filename);

  if (cache_check_file(filename) == 0) { /*finns filen?*/
    if (compare_time(filename, 999999) == 0) { /*Filen finns och är färsk*/
      cache_read_file(filename, &nh);
      return 0;
    }   
  } 
/*om filen inte finns gör api request*/
  if (http_api_request(_URL, &nh) == 0) {
    printf("yay\n");
  }
  printf("NH Size: %d\n", nh->size);
  mt->data = (char*)malloc(nh->size + 1);

  memcpy(mt->data, nh->data, nh->size);
  printf("mt data: %s\n", mt->data);
  *(_Meteo) = mt;

  return 0;
}
