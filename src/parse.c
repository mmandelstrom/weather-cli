#include "../includes/parse.h"
#include "../includes/http.h"
#include "../src/libs/cJSON/cJSON.h"
#include <stdio.h>
#include <time.h>

void check_time_test() {
  time_t current_time = time(NULL);
  struct tm *utc = gmtime(&current_time);

  printf("Sec: %d, min: %d, hour: %d, day: %d, month: %d, year: %d\n",
         utc->tm_sec, utc->tm_min, utc->tm_hour, utc->tm_mday, utc->tm_mon, utc->tm_year + 1900);
}

int parse_json_data_old(HTTP* h) {
  cJSON* root = cJSON_Parse(h->data);
  if (root == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "JSON Parse error: %s\n", error_ptr);
    }
    return 1;
  }

  cJSON *lat  = cJSON_GetObjectItemCaseSensitive(root, "latitude");
  cJSON *lon  = cJSON_GetObjectItemCaseSensitive(root, "longitude");
  cJSON *current_weather = cJSON_GetObjectItemCaseSensitive(root, "current_weather");
  cJSON *temperature = cJSON_GetObjectItemCaseSensitive(current_weather, "temperature");
  
  if (cJSON_IsNumber(lat)) {
      printf("Latitude: %f\n", lat->valuedouble);
  }
  if (cJSON_IsNumber(lon)) {
      printf("Longitude: %f\n", lon->valuedouble);
  }
  if (cJSON_IsNumber(temperature)) {
    printf("Temperature: %.2f\n", temperature->valuedouble);
  }
  if (parse_add_to_file(root) != 0) {
    printf("ERror and stuff");
    return -1;
  }

  return 0;
}

int parse_add_to_file(cJSON* root) {
  const char* filename = "city_data.json";

  FILE *f = fopen(filename, "a+");
  if (!f) {
    printf("Unable to open file: %s\n", filename);
    return -1;
  }

  char* text = cJSON_Print(root);
  fputs(text, f);
  cJSON_free(text); 
  fclose(f);


  if (parse_read_and_print(filename) != 0) {
    printf("Errortime\n");
  }
  return 0;
}

int parse_read_and_print(const char* _Filepath) {
  FILE* fileptr;
  fileptr = fopen(_Filepath, "r");
  if (fileptr == NULL) {
    printf("Failed to open file: %s\n", _Filepath);
    return -1;
  }
  fseek(fileptr, 0L, SEEK_END);
  size_t filesize = ftell(fileptr);
  rewind(fileptr);
  
  char* data = (char*)malloc(filesize);
  if (data == NULL) {
    printf("Failed to allocate memory for data\n");
    return -2;
  }
  
  fread(data, 1, filesize, fileptr);

  cJSON* root = cJSON_Parse(data);
  cJSON* current_weather = cJSON_GetObjectItemCaseSensitive(root, "current_weather");
  
  cJSON* time = cJSON_GetObjectItemCaseSensitive(current_weather, "time");

  char* printed = cJSON_Print(time);
  printf("Printed: %s\n", printed);

  cJSON_free(printed);
  
  return 0;
}

