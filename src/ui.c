#include "ui.h"
#include <stdio.h>

void print_menu(void) {
  printf("\nMenu:\n");
  printf("1. Add todo\n");
  printf("2. Toggle todo status\n");
  printf("3. Delete todo\n");
  printf("4. Save todos\n");
  printf("5. Load todos\n");
  printf("0. Exit\n");
  printf("Enter your choice: ");
}

int get_choice(void) {
  int choice;
  if (scanf("%d", &choice) != 1) {
    while (getchar() != '\n')
      ;
    return -1;
  }
  while (getchar() != '\n')
    ;
  return choice;
}
