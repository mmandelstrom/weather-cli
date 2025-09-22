#ifndef __PARSEDATA_H__
#define __PARSEDATA_H__
#include "../includes/http.h"
#include "../includes/savefile.h"
#include "../src/libs/cJSON/cJSON.h"

int parse_json_data(HTTP* _H, WeatherData** _WeatherData);
void dispose_weather_data(WeatherData* _WeatherData);







#endif 
