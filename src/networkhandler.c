#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include "../includes/cache.h"

char* network_hash_url(char* _URL){
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


int network_read_cache(char* _URL) {

  char* hashed_url = network_hash_url(_URL);

  printf("Hashed: %s\n", hashed_url);

  char* _Data = malloc(150);
  _Data = "asdkjhasdjhkgashjkdaskjlhhaksjdkjhasdhkj";

  cache_create_file(hashed_url, _Data);
  cache_read_file(hashed_url);

  return 0;
}

int network_write_cache(char* _URL, char* _Hash) {
  return 0;
}
