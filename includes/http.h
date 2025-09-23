#ifndef __HTTP_H_
#define __HTTP_H_
#include <stdlib.h>

typedef struct {
  char *data;
  int size;
} HTTP;

int http_api_request(char* _URL);
size_t write_data(void* _Data, size_t _Size, size_t _Element_count, void* _Userp);
void http_clear_data_buffer(HTTP* _Http);
void http_free_memory(HTTP* _Http);

#endif 