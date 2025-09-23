#include <stdio.h>
#include "../includes/http.h"
#include "../includes/savefile.h"

FILE* fptr_g;

int get_weather_data(HTTP* _Http) {

  fptr_g = fopen("data.txt", "r+");
  if (!fptr_g) {
    fptr_g = fopen("data.txt", "w");
    fprintf(fptr_g, "[%s]", _Http->data);
  } else {
    fseek(fptr_g, -1, SEEK_END);
    fprintf(fptr_g, ",%s]", _Http->data);
  }

  fclose(fptr_g);

  return 0; 
}


void read_file() {
  fptr_g = fopen("data.txt", "r");

  char test[2056];
  fgets(test, sizeof(test), fptr_g);

  printf("Data from read_file %s", test);
  
}


