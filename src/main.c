#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include "../includes/http.h"
#include "../includes/utils.h"


int main(){
    char user_input;
    http_t h;
    curl_global_init(CURL_GLOBAL_ALL);
     while(1){
    if (get_api_link(&h)!=0){
        printf("failed to fetch link\n");
        return -1;
    }

    

    if (get_city_data(&h)!=0){
        printf("failed to fetch city data\n");

    }
   
    printf("\nexit? Y/N\n");
    clear_buffer();
    scanf("%c", &user_input);
    if((int)user_input == 121 || (int)user_input == 89){

        break;
    }
        
    }



    curl_global_cleanup();

    return 0;
}