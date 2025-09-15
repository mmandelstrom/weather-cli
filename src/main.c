#include <stdio.h>
#include "../includes/http.h"
#include "../includes/utils.h"


int main(){
    printf("input city: ");
    http_t h;
    if (get_api_link(&h)!=0){
        printf("failed to fetch link\n");



        return -1;
    }
    printf("%s", h.url);


    return 0;
}