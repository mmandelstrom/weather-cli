#include <stdio.h>
#include "../includes/meteo.h"
#include "../includes/parsedata.h"
#include "../includes/networkhandler.h"


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

  printf("Data from meteo: %s\n", m->data);
  
  return 0;

}
