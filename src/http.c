#include <stdio.h>
#include "../includes/http.h"
#include <curl/curl.h>


int get_city_data (http_t *h){
    CURL* handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, h->url);
    curl_easy_setopt(handle, CURLOPT_FAILONERROR,1L);
    CURLcode result = curl_easy_perform(handle);
    if(result == CURLE_HTTP_RETURNED_ERROR){
        printf("failed to fetch from API\n");

        curl_easy_cleanup(handle);
        
        return -1;
    }
    curl_easy_cleanup(handle);

    return 0;







}


