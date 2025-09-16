#ifndef __UTILS_H_
#define __UTILS_H_
#include "../includes/http.h"

typedef struct {
    const char *name;
    double lat;
    double lon;
} cities_t;

extern const cities_t cities[];
int get_meteo_url(http_t* h);
void clear_buffer();
void print_city_list();

#endif



