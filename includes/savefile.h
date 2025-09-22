#ifndef __SAVEFILE_H_
#define __SAVEFILE_H_

#include "http.h"

typedef struct {
    double latitude;
    double longitude;
    double temperature;
    float windspeed;
    int winddirection;
    int is_day;
    char request_time[17];

} WeatherData;

void read_file();
int get_weather_data(HTTP* _Http);

#endif
