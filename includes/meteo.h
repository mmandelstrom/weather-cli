#ifndef __METEO_H__
#define __METEO_H__
#include <stdlib.h>

int meteo_get_city_data(double _Latitude, double _Longitude);

typedef struct {
  char* data;
  size_t size;
} Meteo;

typedef struct {
    double latitude;
    double longitude;
    double generationtime_ms;
    int utc_offset_seconds;
    char timezone[16];
    char timezone_abbreviation[8];
    double elevation;
    char time[32];
    int interval;
    double temperature;
    double windspeed;
    int winddirection;
    int is_day;
    int weathercode;
} MeteoWeatherData;

#endif
