#include "../includes/parse.h"
#include "../includes/http.h"
#include "../external/cjson/cJSON.h"
#include <stdio.h>

int parse_json_data(HTTP* h) {
  cJSON* root = cJSON_Parse(h->data);
  if (root == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "JSON Parse error: %s\n", error_ptr);
    }
    return 1;
  }

  char *printed = cJSON_Print(root);
  if (printed) {
    printf("Root JSON:\n%s\n", printed);
    cJSON_free(printed); 
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
  return 0;
}
