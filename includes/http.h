#ifndef __HTTP_H_
#define __HTTP_H_
#include <stdlib.h>

typedef struct {
  char url[150];
  char *data;
} http_t;

int get_city_data (http_t *h);
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

#endif 
