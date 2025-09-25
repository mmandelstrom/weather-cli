/*#include <stdio.h>
#include <string.h>
#include "libs/cJSON/cJSON.h"
#include "../includes/parsedata.h"
#include "../includes/http.h"

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

    cJSON* current_weather = cJSON_GetObjectItemCaseSensitive(root, "current_weather");

                typedef struct {
    double latitude;
    double longitude;
    double generationtime_ms;
    int utc_offset_seconds;
    char timezone[16];              // "GMT"
    char timezone_abbreviation[8];  // "GMT"
    double elevation;

    // current_weather fält direkt i samma struct
    char time[32];     // "2025-09-25T13:15"
    int interval;      // 900
    double temperature;
    double windspeed;
    int winddirection;
    int is_day;
    int weathercode;
} WeatherData;

        

  cJSON* parsedata_get_number(cJSON* root, const char* name) {
    cJSON* field = cJSON_GetObjectItemCaseSensitive(root, name);
    return (cJSON_IsNumber(field) ? field : NULL);
}

cJSON* parsedata_get_string(cJSON* root, const char* name) {
    cJSON* field = cJSON_GetObjectItemCaseSensitive(root, name);
    return (cJSON_IsString(field) ? field : NULL);
}

  }
  return 0;
}
*/
