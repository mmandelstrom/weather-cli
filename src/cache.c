#include "../includes/cache.h"
#include <stdio.h>

int cache_create_file(char* _Hash, char* _Data) {
    FILE* fptr_g;
    fptr_g = fopen(_Hash, "w");
    fprintf(fptr_g, "%s", _Data);
    fclose(fptr_g);

  return 0; 
}


int cache_read_file(char* _Hash) {
    char stuff[150];
    FILE* fptr_g;
    fptr_g = fopen(_Hash, "r");

    fgets(&stuff, 150, fptr_g);

    printf("Read data: %s\n", stuff);

    return 0;

}   
