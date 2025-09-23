#include <stdio.h>
#include <string.h>
#include "libs/cJSON/cJSON.h"
#include "../includes/parsedata.h"
#include "../includes/http.h"
#include "../includes/savefile.h"

int parse_json_data(HTTP* _H, WeatherData** _WeatherData){
    if (_H->data == NULL) {

        return -1; 
    }

    WeatherData* weatherptr = (WeatherData*) malloc(sizeof(WeatherData));
    if (weatherptr == NULL){
        printf("failed to allocate memory");

        return -1;
    }


    cJSON* root = cJSON_Parse(_H->data);
    if (root == NULL) {
        const char* error_pointer = cJSON_GetErrorPtr();
        if (error_pointer != NULL){
            fprintf(stderr,"JSON error %s\n", error_pointer);

        } 
        return -1;

    
        cJSON* lat = cJSON_GetObjectItemCaseSensitive(root, "latitude");
        cJSON* lon = cJSON_GetObjectItemCaseSensitive(root, "longitude");
        cJSON* current_weather = cJSON_GetObjectItemCaseSensitive(root, "current_weather");
        cJSON* temperature = cJSON_GetObjectItemCaseSensitive(current_weather, "temperature");
        cJSON* time = cJSON_GetObjectItemCaseSensitive(current_weather, "time");
        cJSON* wind_speed = cJSON_GetObjectItemCaseSensitive(current_weather, "wind_speed");
        cJSON* wind_direction = cJSON_GetObjectItemCaseSensitive(current_weather, "wind_direction");
        cJSON* is_day = cJSON_GetObjectItemCaseSensitive(current_weather, "is_day");

        if (!cJSON_IsNumber(lat) ||
            !cJSON_IsNumber(lon) ||
            !cJSON_IsNumber(temperature) ||
            !cJSON_IsString(time) ||
            !cJSON_IsNumber(wind_speed) ||
            !cJSON_IsNumber(wind_direction) ||
            !cJSON_IsNumber(is_day)) {
            printf("Error: Missing or invalid data in JSON response\n");
            cJSON_Delete(root);
            free(weatherptr);
            return -1;
        }
    
        weatherptr->latitude = lat->valuedouble;
        weatherptr->longitude = lon->valuedouble;
        weatherptr->temperature = temperature->valuedouble;
        strcpy(weatherptr->request_time, time->valuestring);
        weatherptr->windspeed = wind_speed->valuedouble;
        weatherptr->winddirection = wind_direction->valuedouble;
        weatherptr->is_day = is_day->valueint;
        

        if (_WeatherData != NULL){
            *(_WeatherData) = weatherptr;

        }
  }
  return 0;
}


