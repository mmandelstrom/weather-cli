#include <stdio.h>
#include "../includes/http.h"
#include "../includes/meteo.h"

int meteo_get_city_data(double _Latitude, double _Longitude) {
  char url[150];
  sprintf(url,
          "https://api.open-meteo.com/v1/"
          "forecast?latitude=%.4f&longitude=%.4f&current_weather=true",
          _Latitude, _Longitude);

  return 0;
}

