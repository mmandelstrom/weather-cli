#ifndef __UTILS_H_
#define __UTILS_H_
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <sys/stat.h>
#include <time.h>

static char* my_strdup(const char* str) {
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

static char* utils_hash_url(char* _URL){
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


static int compare_time(char* _Filename, int _Interval){
  char filepath[60];
  sprintf(filepath, "cache/%s.JSON", _Filename);
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

#endif



