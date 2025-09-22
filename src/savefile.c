#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"
#include "savefile.h"

FILE* fptr_g;

int get_weather_data(HTTP* _Http, char* _City_name) {
    WeatherData wd;
    memset(&wd, 0, sizeof(WeatherData));

    wd.latitude = 12.3456;
    wd.longitude = 12.3456;
    wd.temperature = 0;
    wd.windspeed = 4.5;
    wd.winddirection = 0;
    wd.is_day = 0;
    strcpy(wd.request_time, "2025-09-22T11:45");

    
    fptr_g = fopen("data.bin", "ab+");
    
    if (fwrite(&wd, sizeof(WeatherData), 1, fptr_g) != 0) {
        printf("Successfully written struct to file\n");
    }   else {
        printf("Failed writing struct to file!\n");
    }

    rewind(fptr_g);

    WeatherData wd2;

    fread(&wd2, sizeof(wd2), 1, fptr_g);

    printf("%lf", wd2.latitude);

    fclose(fptr_g);
    return 0;
}