#include <stdio.h>
#include "../includes/cities.h"

Cities cities_g;
int main(){
  cities_init(&cities_g);


/*  char user_input;
  http_t h;
  curl_global_init(CURL_GLOBAL_ALL);
    
  printf("Welcome!\n");
  printf("Below you can find a list of available cities\n");

    while(1){
      print_city_list();

      printf("Enter a city you would like a weather report for: ");

      if (get_meteo_url(&h) != 0){
        continue; 
      }

      if (get_city_data(&h)!= 0){
          printf("failed to fetch city data\n");
      }
   
      printf("\nWould you like to continue? Y/N: ");
      
      scanf("%c", &user_input);

      if(user_input == 'n' || user_input == 'N'){
          break;
      }
      
      clear_buffer();

    }

    curl_global_cleanup();
*/
    return 0;
}
