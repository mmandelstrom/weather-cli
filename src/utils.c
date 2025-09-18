#include "../includes/http.h"
#include <stdio.h>
#include "../includes/utils.h"
#include <string.h>
#include <strings.h>



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
