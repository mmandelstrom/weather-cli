#ifndef __PARSE_H__
#define __PARSE_H__
#include "../includes/http.h"
#include "../external/cjson/cJSON.h"

typedef struct{
    cJson name;
    
    cJson temp;
    
    cJson lat;
    
    cJson lon;
} Meteo_data;

int parse_json_data(HTTP* h);

int parse_add_to_file(cJson* root);


#endif