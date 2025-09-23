#ifndef __NETWORKHANDLER_H__
#define __NETWORKHANDLER_H__


char* network_hash_url(char* _URL);

int network_read_cache(char* _URL);

int network_write_cache(char* _URL, char* _Hash);

#endif
