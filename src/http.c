#include <stdio.h>
#include "../includes/http.h"
#include <curl/curl.h>
#include <string.h>

int get_city_data (http_t *h){
  CURL* handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, h->url);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &h);  
  CURLcode result = curl_easy_perform(handle);

  if(result != CURLE_OK){
      printf("Failed to fetch data from meteo API\n");
      curl_easy_cleanup(handle);
      return -1;
  }
  curl_easy_cleanup(handle);

  return 0;
}


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
  size_t bytes = size * nmemb;
  printf("Chunk recieved: %zu bytes\n", bytes);
  http_t *h = (http_t*)userp;

  h->data = malloc(bytes + 1);
  memcpy(h->data, buffer, bytes);

  printf("This is the data: %s\n", h->data);

  return bytes;
}



