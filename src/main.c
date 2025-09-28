#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/linkedlist.h"
#include "../includes/utils.h"

LinkedList cities_g;

int main(){
 bool runLoop = true; 
 while (runLoop) {

    cities_init(&cities_g);

    if (utils_break_loop() != 0) {
      break;
    }
  }


   
  return 0;
}
