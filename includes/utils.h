#ifndef __UTILS_H_
#define __UTILS_H_
#include <string.h>
#include <stdlib.h>

static inline char* my_strdup(const char* str) {
  if (!str) return NULL;
  size_t len = strlen(str) + 1;
  char* copy = (char*)malloc(len);
  if (copy == NULL) {
    return NULL;
  }
  memcpy(copy, str, len);   
  
  return copy;
}

void print_welcome_message();
int get_user_input(char** _InputPtr);
int break_loop();

#endif



