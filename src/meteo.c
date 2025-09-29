#include <stdio.h>
#include <string.h>
#include "../includes/utils.h"
#include "../includes/meteo.h"
#include "../includes/parsedata.h"
#include "../includes/networkhandler.h"
#include "../includes/parsedata.h"

void meteo_print_weatherdata(MeteoWeatherData* _MWD);

int meteo_get_weather_data(double _Latitude, double _Longitude, char* _CityName) {
  char url[150];
  sprintf(url,
          "https://api.open-meteo.com/v1/"
          "forecast?latitude=%.4f&longitude=%.4f&current_weather=true",
          _Latitude, _Longitude);
  
  Meteo* m = NULL;
  
  if (networkhandler_get_data(url, &m, FLAG_WRITE) != 0) {
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

  MWD.name = _CityName;
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
  meteo_print_full_weatherdata(&MWD);
  free(m);

  return 0;

}

cJSON* meteo_get_city_data(char* _CityName) {
  char url[150];
  sprintf(url,
          "https://geocoding-api.open-meteo.com/v1/search?name=%s&count=1",
          _CityName);
  
  Meteo* m = NULL;
  if (networkhandler_get_data(url, &m, FLAG_NO_WRITE) != 0) {
    printf("Failed to get city data\n");
    return NULL;
  }

  cJSON* root = cJSON_Parse(m->data);
    if (root == NULL) {
      const char* error_pointer = cJSON_GetErrorPtr();
      if (error_pointer != NULL){
          fprintf(stderr,"JSON error %s\n", error_pointer);
      }
        return NULL;
    }

  return root; /*Needs to be destroyed by caller*/

}

void meteo_print_weatherdata(MeteoWeatherData* _MWD) {
  printf("\n");
  printf("\t+-----------------------------+\n");
  printf("\t %-27s \n", _MWD->name);
  printf("\t+-----------------------------+\n");
  printf("\t Temperature:%12.2f °C \n", _MWD->temperature);
  printf("\t Elevation:  %12.2f m  \n", _MWD->elevation);
  printf("\t Windspeed:  %12.2f m/s\n", _MWD->windspeed);
  printf("\t+-----------------------------+\n");  
  printf("\n");
}

void meteo_print_full_weatherdata(MeteoWeatherData* _MWD) {
  printf("Would you like to get the full weather report? Y/N: ");

  if (utils_continue() != 0) {
    return;
  }

  printf("\n");
  printf("\t+-------------------------------------------+\n");
  printf("\t %-41.41s \n", _MWD->name);
  printf("\t+-------------------------------------------+\n");

  /* label (vänsterjust 16) + mellanslag + värdeblock (högerjust 24) = 41 */
  printf("\t %-16s %24.4f \n", "Latitude:", _MWD->latitude);
  printf("\t %-16s %24.4f \n", "Longitude:", _MWD->longitude);
  printf("\t %-16s %24.24s \n", "Timezone:", _MWD->timezone);        /* sträng, ev. trunkeras */
  printf("\t %-16s %22.2f m \n", "Elevation:", _MWD->elevation);       /* 22 + ' m' = 24 */
  printf("\t %-16s %24.24s \n", "Time:", _MWD->time);            /* sträng, ev. trunkeras */
  printf("\t %-16s %24d \n",    "Interval:", _MWD->interval);
  printf("\t %-16s %21.2f °C \n","Temperature:", _MWD->temperature);     /* 21 + ' °C' = 24 */
  printf("\t %-16s %20.2f m/s \n","Windspeed:", _MWD->windspeed);       /* 20 + ' m/s' = 24 */
  printf("\t %-16s %22d ° \n",  "Winddirection:", _MWD->winddirection);   /* 22 + ' °' = 24 */
  printf("\t %-16s %24d \n",    "Weathercode:", _MWD->weathercode);
  printf("\t+-------------------------------------------+\n");
  printf("\n");  
}
  


