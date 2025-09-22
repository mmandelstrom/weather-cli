#ifndef __PARSE_H__
#define __PARSE_H__
#include "../includes/http.h"
#include "../src/libs/cJSON/cJSON.h"

typedef struct {
  cJSON name;
  cJSON temp;
  cJSON lat;
  cJSON lon;
} Meteo_data;
int parse_json_data_old(HTTP* h);
int parse_add_to_file(cJSON* root);
int parse_read_and_print(const char* _Filepath);
void check_time_test();

#endif

