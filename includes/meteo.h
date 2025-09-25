#ifndef __METEO_H__
#define __METEO_H__
int meteo_get_city_data(double _Latitude, double _Longitude);

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
} WeatherData;

#endif
