#include <stdio.h>
#include "../includes/utils.h"

void print_welcome_message() {
  printf("Welcome!\n");
  printf("Please select a city from the list below\n");
}


int get_user_input(char** _InputPtr) {
  int buff_size = 25;
  char* user_input = (char*)malloc(buff_size);
  if (user_input == NULL) {
    printf("Unable to allocate memory for user input\n");
    return -1;
  }
  printf("Input city: ");
  fgets(user_input, buff_size, stdin);
  user_input[strcspn(user_input, "\n")] = '\0';

  if ((_InputPtr) != NULL) {
    *(_InputPtr) = user_input;
  }

  return 0;
}

int break_loop() {
  printf("Would you like to get the weather for another city? Y/N: ");
  char ch;

  while ((ch = getchar()) != '\n' && ch != EOF) { 
     if (ch == 'N' || ch == 'n') {
    return 1;
    }
  }
   return 0;
}
