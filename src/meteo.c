#include <stdio.h>
#include <string.h>
#include "../includes/meteo.h"
#include "../includes/parsedata.h"
#include "../includes/networkhandler.h"
#include "../includes/parsedata.h"

void meteo_print_weatherdata(MeteoWeatherData* _MWD);

int meteo_get_city_data(double _Latitude, double _Longitude) {
  char url[150];
  sprintf(url,
          "https://api.open-meteo.com/v1/"
          "forecast?latitude=%.4f&longitude=%.4f&current_weather=true",
          _Latitude, _Longitude);
  
  Meteo* m = NULL;
  
  if (networkhandler_get_data(url, &m) != 0) {
    printf("Failed to get city data\n");
    return -1;
  }

  MeteoWeatherData MWD = {0};

   cJSON* root = cJSON_Parse(m->data);
    if (root == NULL) {
      const char* error_pointer = cJSON_GetErrorPtr();
      if (error_pointer != NULL){
          fprintf(stderr,"JSON error %s\n", error_pointer);
      }
        return -1;
    }

  cJSON* current_weather = cJSON_GetObjectItemCaseSensitive(root, "current_weather");

  MWD.latitude = parsedata_get_double(root, "latitude");
  MWD.longitude = parsedata_get_double(root, "longitude");
  MWD.generationtime_ms = parsedata_get_double(root, "generationtime_ms");
  MWD.utc_offset_seconds = parsedata_get_int(root, "utc_offset_seconds");
  strcpy(MWD.timezone, parsedata_get_string(root, "timezone"));
  strcpy(MWD.timezone_abbreviation, parsedata_get_string(root, "timezone_abbreviation"));
  MWD.elevation = parsedata_get_double(root, "elevation");
  strcpy(MWD.time, parsedata_get_string(current_weather, "time"));
  MWD.interval = parsedata_get_int(current_weather, "interval");
  MWD.temperature = parsedata_get_double(current_weather, "temperature");
  MWD.windspeed = parsedata_get_double(current_weather, "windspeed");
  MWD.winddirection = parsedata_get_int(current_weather, "winddirection");
  MWD.is_day = parsedata_get_int(current_weather, "is_day");
  MWD.weathercode = parsedata_get_int(current_weather, "weathercode");

  meteo_print_weatherdata(&MWD);
  free(m);

  return 0;

}


void meteo_print_weatherdata(MeteoWeatherData* _MWD) {
  printf("Weather data for _CITY_\n");
  printf("\tTemperature: %.2f Celsius\n", _MWD->temperature);
  printf("\tElevation: %.2f Meters\n", _MWD->elevation);
  printf("\tWindspeed: %.2f M/S\n", _MWD->windspeed);
}
