#include "../includes/linkedlist.h"
#include <stdio.h>
#include "../includes/utils.h"
#include "../includes/meteo.h"
#include "../includes/city.h"

/*-------------Internal function definitions----------------*/

const char* cities_list = "Stockholm:59.3293:18.0686\n"
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


/*--------------------------------------------------------*/

int city_parse_list(LinkedList* _LinkedList, const char* list) {
  char* list_copy = utils_strdup(list);
  if (list_copy == NULL) {
    printf("Failed to allocate memory for list\n");
    return -1;
  }

  char* ptr = list_copy;
  char* name = NULL;
  char* lat_str = NULL;
  char* lon_str = NULL;
 
  	do {
		if(name == NULL) {
			name = ptr;
		}
		else if(lat_str == NULL) {
			if(*(ptr) == ':') {
				lat_str = ptr + 1;
				*(ptr) = '\0';
			}
		}
		else if(lon_str == NULL) {
			if(*(ptr) == ':') {
				lon_str = ptr + 1;
				*(ptr) = '\0';
			}
		}
		else {
			if(*(ptr) == '\n') {
				*(ptr) = '\0';

				cities_add(_LinkedList, name, atof(lat_str), atof(lon_str), NULL);

				name = NULL;
				lat_str = NULL;
				lon_str = NULL;
			}
		}

		ptr++;

	} while (*(ptr) != '\0');



    return 0;
}


int city_get_info(LinkedList* _CityList) {
    
  char* user_input = NULL;
  if (utils_get_user_input(&user_input) != 0) {
    free(user_input);
    printf("Please try again\n");
    }

  City* user_city = NULL;

  if (ll_get(_CityList, user_input, &user_city) != 0) {
    printf("Failed to get city\n");
    free(user_input);
    return -1;
  }

  printf("user_city: %s\n", user_city->name);

  meteo_get_city_data(user_city->latitude, user_city->longitude, user_city->name);
  
  free(user_city);
  free(user_input);
  user_input = NULL;

  return 0;
}
