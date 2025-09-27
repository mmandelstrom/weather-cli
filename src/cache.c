#include "../includes/cache.h"
#include "../includes/networkhandler.h"
#include <stdio.h>
#include <errno.h>

/*Skapar fil*/
int cache_create_file(char* _HashedName, char* _Data) {
  if (_HashedName == NULL || _Data == NULL) {
    return -1;
  }  

  char filepath[50];
  sprintf(filepath, "cache/%s.JSON", _HashedName);
  
  FILE* fptr;
  fptr = fopen(filepath, "w");
  if (fptr == NULL) {
    perror("fopen");
    fclose(fptr);
    return -1;
  }

  fprintf(fptr, "%s", _Data);
  fclose(fptr);

  return 0; 
}

/*Läser från fil o skickar datan till vår NH pointer*/
int cache_read_file(char* _HashedName, NetworkHandler** _NhPtr) {
  if (_HashedName == NULL || _NhPtr == NULL) {
    return -1;
  }

  *_NhPtr = NULL;
  FILE* fptr;
  char filepath[50];
  sprintf(filepath, "cache/%s.JSON", _HashedName);

  fptr = fopen(filepath, "r");
  if (fptr == NULL) {
    perror("fopen");
    fclose(fptr);
    return -1;
  }

  if (fseek(fptr, 0, SEEK_END) != 0) {
    perror("fseek");
    fclose(fptr);
    return -1;
  }

  long size = ftell(fptr);
  if (size < 0) {
    perror("ftell");
    fclose(fptr);
    return -1;
  }

  if (fseek(fptr, 0, SEEK_SET) != 0) {
    perror("fseek");
    fclose(fptr);
    return -1;
  }

  NetworkHandler* nh = calloc(1, sizeof(*nh));
  if (nh == NULL) {
    perror("calloc");
    fclose(fptr);
    return -1;
  }

  nh->data = (char*)malloc((size_t)size + 1);
  if (nh->data == NULL) {
    perror("malloc");
    fclose(fptr);
    free(nh);
    return -1;
  }
  
  size_t bytes_read = fread(nh->data, 1, size, fptr);
  if (bytes_read != (size_t)size) {
    perror("fread");
    fclose(fptr);
    free(nh->data);
    free(nh);
    return -1;
  }

  nh->size = (size_t)size;

  fclose(fptr);

  *(_NhPtr)= nh;

  return 0;

}   

/*Kollar om filen existerar*/
int cache_check_file(char* _HashedName) {
  if (_HashedName == NULL) {
    return -1;
  }

  char filepath[50];
  sprintf(filepath, "cache/%s.JSON", _HashedName);
  
  FILE* fptr;
  fptr = fopen(filepath, "r");
  if (fptr == NULL) {
    perror("fopen");
    return 1; /*File does not exist*/
  }

  fclose(fptr);
  return 0; /*File exists*/
}
