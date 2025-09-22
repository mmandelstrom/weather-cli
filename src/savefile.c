#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parsedata.h"
#include "http.h"
#include "savefile.h"

FILE* fptr_g;

int get_weather_data(HTTP* _Http) {
    WeatherData* wd;
    memset(wd, 0, sizeof(WeatherData));

    if (parse_json_data(_Http, &wd) != 0) {
        printf("Failed to parse JSON data\n");
        return -1;
    }

    fptr_g = fopen("data.bin", "ab+");
    
    if (fwrite(wd, sizeof(WeatherData), 1, fptr_g) != 0) {
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