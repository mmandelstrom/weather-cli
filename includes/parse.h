#ifndef __PARSE_H__
#define __PARSE_H__
#include "../includes/http.h"
#include "../includes/cJSON.h"

typedef struct {
  cJSON name;
  cJSON temp;
  cJSON lat;
  cJSON lon;
} Meteo_data;
int parse_json_data(HTTP* h);
int parse_add_to_file(cJSON* root);

#endif

