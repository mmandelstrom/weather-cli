#include "../includes/http.h"
#include <stdio.h>
#include "../includes/utils.h"
#include <string.h>
#include <strings.h>


    const char* cities = 
    "Stockholm:59.3293:18.0686\n" 
    "Göteborg:57.7089:11.9746\n" 
    "Malmö:55.6050:13.0038\n" 
    "Uppsala:59.8586:17.6389\n" 
    "Västerås:59.6099:16.5448\n" 
    "Örebro:59.2741:15.2066\n" 
    "Linköping:58.4109:15.6216\n" 
    "Helsingborg:56.0465:12.6945\n" 
    "Jönköping:57.7815:14.1562\n" 
    "Norrköping:58.5877:16.1924\n" 
    "Lund:55.7047:13.1910\n" 
    "Gävle:60.6749:17.1413\n" 
    "Sundsvall:62.3908:17.3069\n" 
    "Umeå:63.8258:20.2630\n" 
    "Luleå:65.5848:22.1567\n" 
    "Kiruna:67.8558:20.2253\n";

    const char* scan = cities;

    char input[21];
    char buffer[21];
    double lat, lon;
    int found = 0;

    printf("Pick a city from the following list:\n");

    while (*scan != '\0') {

        sscanf(scan, "%[^:]:%lf:%lf", buffer, &lat, &lon);
        printf("%s\n", buffer);

        scan = strchr(scan, '\n');
        
        if (scan == NULL) {
            break;
        } else {
            scan++;
        }
    }

    printf("Input city: \n");


/*
int get_meteo_url(http_t *h){
  char city[21];
  int i;

  if (fgets(city, sizeof(city), stdin) == NULL) {
    printf("Failed to get user input\n");
    return -1;


  }

  city[strcspn(city, "\n")] = '\0';

  int found = -1;

   sprintf(h->url,
          "https://api.open-meteo.com/v1/forecast?latitude=%.4f&longitude=%.4f&current_weather=true",
          cities[i].lat, cities[i].lon);

  return 0;
}

void clear_buffer (){
    while ( getchar() != '\n' );
}

*/
