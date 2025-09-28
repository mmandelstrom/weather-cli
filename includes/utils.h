#ifndef __UTILS_H_
#define __UTILS_H_

char* utils_strdup(const char* str); 
int utils_get_user_input(char** _InputPtr);
int utils_break_loop();
char* utils_hash_url(char* _URL);
int utils_compare_time(char* _Filename, int _Interval);
int utils_create_folder(const char* _Path);

#endif



