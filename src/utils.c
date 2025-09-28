#include "../includes/utils.h"
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>

char* utils_strdup(const char* str) {
  if (!str) return NULL;
  size_t len = strlen(str) + 1;
  char* copy = (char*)malloc(len);
  if (copy == NULL) {
    return NULL;
  }
  memcpy(copy, str, len);   
  
  return copy;
}

int utils_get_user_input(char** _InputPtr) {
  int buff_size = 25;
  char* user_input = (char*)malloc(buff_size);
  if (user_input == NULL) {
    printf("Unable to allocate memory for user input\n");
    return -1;
  }
  printf("Input city: ");
  if (fgets(user_input, buff_size, stdin) == NULL) {
    free(user_input);
    return -1;
  }

  size_t len = strlen(user_input);
  if (len > 0 && user_input[len-1] == '\n') {
    user_input[len-1] = '\0';   /* newline fick plats, ta bort den */
  } else {
    /* newline låg kvar i stdin, töm resten av raden */
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

  if ((_InputPtr) != NULL) {
    *(_InputPtr) = user_input;
  }

  return 0;
}

int utils_break_loop() {
  printf("Would you like to get the weather for another city? Y/N: ");
  char ch;

  while ((ch = getchar()) != '\n' && ch != EOF) { 
     if (ch == 'N' || ch == 'n') {
    return 1;
    }
  }
   return 0;
}

int utils_create_folder(const char* _Path) {
	#if defined _WIN32
		bool success = CreateDirectory(_Path, NULL);
		if(success == false)
		{
			DWORD err = GetLastError();
			if(err == ERROR_ALREADY_EXISTS)
				return 1;
			else
				return -1;

		}
	#else
		int success = mkdir(_Path, 0777);
		if(success != 0)
		{
			if(errno == EEXIST)
				return 1;
			else
				return -1;

		}
	#endif

	return 0;
}

int utils_compare_time(char* _Filename, char* _Path, int _Interval){
  char filepath[60];
  sprintf(filepath, "%s/%s.json",_Path, _Filename);
  printf("compare: %s\n", filepath);

	struct stat file_info;
    if (stat(filepath, &file_info) == -1) {
        perror("stat");
        return -1;
    }

    time_t now = time(NULL);
    double diff = difftime(now, file_info.st_mtime);

    if (diff < _Interval) { 
      return 0;
    } else { 
      return 1;
    }
}

char* utils_hash_url(char* _URL){
  unsigned int i;

  unsigned char digest[EVP_MAX_MD_SIZE]; /* Allocate buffer for all functions */
  unsigned int digest_len; /* Actual length in bytes of final hash*/

  EVP_MD_CTX *ctx = EVP_MD_CTX_new(); /*OBject that saves state, hashing algoritm etc*/
  if (!ctx) {
      fprintf(stderr, "Could not create EVP_MD_CTX\n");
      return NULL;
  }

  if (EVP_DigestInit_ex(ctx, EVP_md5(), NULL) != 1) { /*Sets MD5 as algoritm for ctx object*/
      fprintf(stderr, "EVP_DigestInit_ex failed\n");
      EVP_MD_CTX_free(ctx);
      return NULL;
  }

  if (EVP_DigestUpdate(ctx, _URL, strlen(_URL)) != 1) { /*Inputs the bytes from text to ctx object*/
      fprintf(stderr, "EVP_DigestUpdate failed\n");
      EVP_MD_CTX_free(ctx);
      return NULL;
  }

  if (EVP_DigestFinal_ex(ctx, digest, &digest_len) != 1) { /*Finalizes data transfer and fills digest buffer with bytes (16for md5)*/
      fprintf(stderr, "EVP_DigestFinal_ex failed\n");
      EVP_MD_CTX_free(ctx);
      return NULL;
  }

  EVP_MD_CTX_free(ctx); /*Free ctx object so it doesnt leak*/

  char* md5_string = (char*)malloc(digest_len * 2 + 1);
   /*cReate buffer for hashed string*/
  
  for (i = 0; i < digest_len; i++) { /*Convert to hex*/
      sprintf(&md5_string[i*2], "%02x", digest[i]);
  }
  md5_string[digest_len * 2] = '\0';

  
  return md5_string; /* Needs to be freed by caller*/
}









