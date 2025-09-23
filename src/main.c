#include <stdbool.h>
#include "../includes/networkhandler.h"
#include <stdio.h>
#include <stdlib.h>


/*LinkedList cities_g;*/

int main(){
/*  bool runLoop = true; 
  while (runLoop) {
  
  cities_init(&cities_g);
  }
*/

  char url[100];
  sprintf(url,
          "https://api.open-meteo.com/v1/"
          "forecast?latitude=%.4f&longitude=%.4f&current_weather=true",
          58.4109, 15.6216);

  network_read_cache(url);
    
  return 0;
}
