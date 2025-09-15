#include "../includes/http.h"
#include <stdio.h>

int get_api_link(http_t *h){
    char city[21];
    if (scanf("%20s", city)!=1){
        printf("failed to fetch city\n");


        return -1;
    }

    sprintf(h->url ,"https://geocoding-api.open-meteo.com/v1/search?name=%s&count=1&language=sv&format=json", city);




    return 0;
}
