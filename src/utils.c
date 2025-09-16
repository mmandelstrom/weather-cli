#include "../includes/http.h"
#include <stdio.h>
#include "../includes/utils.h"
#include <string.h>
#include <strings.h>

const cities_t cities[] = {
  {"Stockholm", 59.3293, 18.0686},
  {"Göteborg", 57.7089, 11.9746},
  {"Malmö", 55.6050, 13.0038},
  {"Uppsala", 59.8586, 17.6389},
  {"Västerås", 59.6099, 16.5448},
  {"Örebro", 59.2741, 15.2066},
  {"Linköping", 58.4109, 15.6216},
  {"Helsingborg", 56.0465, 12.6945},
  {"Jönköping", 57.7815, 14.1562},
  {"Norrköping", 58.5877, 16.1924},
  {"Lund", 55.7047, 13.1910},
  {"Gävle", 60.6749, 17.1413},
  {"Sundsvall", 62.3908, 17.3069},
  {"Umeå", 63.8258, 20.2630},
  {"Luleå", 65.5848, 22.1567},
  {"Kiruna", 67.8558, 20.2253}
};

int city_count = sizeof(cities) / sizeof(cities[0]);

int get_meteo_url(http_t *h){
  char city[21];
  int i;

  if (fgets(city, sizeof(city), stdin) == NULL) {
    printf("Failed to get user input\n");
    return -1;

  }

  city[strcspn(city, "\n")] = '\0';

  int found = -1;

  for (i = 0; i < city_count; i++) {
    if (strcasecmp(city, cities[i].name) == 0) {
      found = i;
      break;
    }
  }

  if (found < 0) {
    printf("Invalid city entered. Please input a city name from the list below\n");
    return -1;
  }

  sprintf(h->url,
          "https://api.open-meteo.com/v1/forecast?latitude=%.4f&longitude=%.4f&current_weather=true",
          cities[i].lat, cities[i].lon);

  return 0;
}

void clear_buffer (){
    while ( getchar() != '\n' );
}


void print_city_list() {
  int i;
  
  for (i = 0; i < city_count; i++) {
    printf("- %s\n", cities[i].name);
  }
}
