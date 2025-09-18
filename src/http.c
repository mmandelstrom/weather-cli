#include "../includes/http.h"
#include "../includes/cities.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

int meteo_get_new_city(char *_Name);

int meteo_get_city_data(city *_City) {
  char url[150];
  http_t h;
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

  printf("DAta: %s\n", h.data);

  curl_easy_cleanup(handle);

  return 0;
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
  size_t bytes = size * nmemb;
  printf("Chunk recieved: %zu bytes\n", bytes);
  http_t *h = (http_t *)userp;
  h->size = bytes + 1;
  h->data = malloc(h->size);
  memcpy(h->data, buffer, bytes);

  return bytes;
}

void http_clear_data_buffer(http_t *h) {
  if (h->data) {
    memset(h->data, 0, h->size);
  }
}

void http_free_memory(http_t *h) { free(h->data); }
