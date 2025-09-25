#ifndef __CACHE_H__
#define __CACHE_H__

#include "../includes/networkhandler.h"

int cache_create_file(char* _Hash, char* _Data);
int cache_read_file(char* _Filename, NetworkHandler** _NhPtr);
int cache_check_file(char* _Filename);

#endif