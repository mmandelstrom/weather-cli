#include "../includes/http.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>


int http_api_request(char* _URL) {
  HTTP h = {0};

  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, _URL);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&h);
  CURLcode result = curl_easy_perform(handle);

  if (result != CURLE_OK) {
    printf("Failed to fetch data from API\n");
    curl_easy_cleanup(handle);
    return -1;
  }

  curl_easy_cleanup(handle);

  free(h.data);
  return 0;
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
  size_t bytes = size * nmemb;
  printf("Chunk recieved: %zu bytes\n", bytes);
  HTTP *h = (HTTP *)userp;
  
  char *newptr = realloc(h->data, h->size + bytes + 2);
  if (newptr == NULL) {
    printf("Unable to reallocate memory\n");
    return -1;
  }
  h->data = newptr;
  h->size += sizeof(*newptr);
  memcpy(h->data, buffer, bytes);


  return bytes;
}



void http_free_memory(HTTP *h) { free(h->data); }