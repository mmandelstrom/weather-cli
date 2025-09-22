#include "../includes/cities.h"
#include "../includes/utils.h"
Cities cities_g;

int main(){
  
  print_welcome_message();
  cities_init(&cities_g);
    
  return 0;
}
