#ifndef __HTTP_H_
#define __HTTP_H_
#include <stdlib.h>
#include "../includes/cities.h"

typedef struct {
  char *data;
  int size;
} HTTP;

int meteo_get_new_city(char* _Name);
int meteo_get_city_data(City* _City);
size_t write_data(void* _Data, size_t _Size, size_t _Element_count, void* _Userp);
void http_clear_data_buffer(HTTP* _Http);
void http_free_memory(HTTP* _Http);

#endif 
