#ifndef __UTILS_H_
#define __UTILS_H_
#include "../includes/http.h"
#include <string.h>

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

#endif



