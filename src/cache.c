#include "../includes/cache.h"
#include "../includes/networkhandler.h"
#include <stdio.h>
/*Skapar fil*/
int cache_create_file(char* _Hash, char* _Data) {
    FILE* fptr_g;
    fptr_g = fopen(_Hash, "w");
    fprintf(fptr_g, "%s", _Data);
    fclose(fptr_g);

  return 0; 
}

/*Läser från fil o skickar datan till vår NH pointer*/
int cache_read_file(char* _Hash, NetworkHandler** _NhPtr) {
  NetworkHandler* buffer = calloc(1, sizeof *buffer);
  buffer->data = (char*)malloc(sizeof(1024));
  FILE* fptr_g;
  fptr_g = fopen(_Hash, "r");

  fgets(buffer->data, 1024, fptr_g);

  *(_NhPtr) = buffer;

  return 0;

}   

/*Kollar om filen existerar*/
int cache_check_file(char* _Filename) {
  FILE* fptr;
  fptr = fopen(_Filename, "r");
  if (fptr == NULL) { 
    return 1; /*File does not exist*/
  }

  fclose(fptr);
  return 0; /*File exists*/
}
