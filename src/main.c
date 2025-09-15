#include <stdio.h>
#include <curl/curl.h>
#include "../includes/http.h"
#include "../includes/utils.h"


int main(){
    printf("input city: ");
    http_t h;
    if (get_api_link(&h)!=0){
        printf("failed to fetch link\n");

        return -1;
    }

    curl_global_init(CURL_GLOBAL_ALL);

    if (get_city_data(&h)!=0){
        printf("failed to fetch city data\n");

        return -1;
    }

    curl_global_cleanup();

    return 0;
}