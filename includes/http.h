#ifndef __HTTP_H_
#define __HTTP_H_
#include <stdlib.h>
#include "../includes/cities.h"

typedef struct {
  char *data;
  int size;
} http_t;

int meteo_get_new_city(char* _Name);
int meteo_get_city_data(city* _City);
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
void http_clear_data_buffer(http_t *h);
void http_free_memory(http_t *h);

#endif 
