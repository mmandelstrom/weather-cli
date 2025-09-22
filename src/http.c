#include "../includes/http.h"
#include "../includes/cities.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include "../includes/savefile.h"


int meteo_get_new_city(char *_Name);

int meteo_get_city_data(City *_City) {
  char* url = (char*)malloc(150);
  HTTP h = {0};

  sprintf(url,
          "https://api.open-meteo.com/v1/"
          "forecast?latitude=%.4f&longitude=%.4f&current_weather=true",
          _City->latitude, _City->longitude);

  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, url);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&h);
  CURLcode result = curl_easy_perform(handle);

  if (result != CURLE_OK) {
    printf("Failed to fetch data from meteo API\n");
    curl_easy_cleanup(handle);
    return -1;
  }


  curl_easy_cleanup(handle);

  if (get_weather_data(&h) != 0) {
    printf("Failed to get weather data\n");
    return -1;
  } 

  free(url);
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

void http_clear_data_buffer(HTTP *h) {
  if (h->data) {
    memset(h->data, 0, h->size);
  }
}

void http_free_memory(HTTP *h) { free(h->data); }
