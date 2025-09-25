#ifndef __NETWORKHANDLER_H__
#define __NETWORKHANDLER_H__

#include <stdlib.h>

typedef struct {
  char *data;
  size_t size;
} NetworkHandler;

int networkhandler_get_data(char* _URL);

#endif

