#include "../includes/networkhandler.h"
#include "../includes/http.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>



int http_api_request(char* _URL, NetworkHandler** _NhPtr) { /*Skapar curl objekt och gör curl request och skickar datan till vår pointer*/
  NetworkHandler* nh = malloc(sizeof(NetworkHandler*));

  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, _URL);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)nh);
  CURLcode result = curl_easy_perform(handle);

  if (result != CURLE_OK) {
    printf("Failed to fetch data from API\n");
    curl_easy_cleanup(handle);
    return -1;
  }

  curl_easy_cleanup(handle);
  
  *(_NhPtr) = nh; /*Needs to be freed by caller*/

  return 0;
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) { /*Sparar datan från curl request i nh->data*/
  size_t bytes = size * nmemb;
  printf("Chunk recieved: %zu bytes\n", bytes);
  NetworkHandler *nh = (NetworkHandler *)userp;
  
  char *newptr = realloc(nh->data, nh->size + bytes + 2);
  if (newptr == NULL) {
    printf("Unable to reallocate memory\n");
    return -1;
  }
  nh->data = newptr;
  nh->size += sizeof(*newptr);
  memcpy(nh->data, buffer, bytes);

  return bytes;
}
