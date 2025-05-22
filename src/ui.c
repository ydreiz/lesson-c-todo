#include <stdio.h>

#include "todo.h"
#include "ui.h"

void print_menu(void) {
  printf("\nMenu:\n");
  printf("1. Add todo\n");
  printf("2. Toggle todo status\n");
  printf("3. Edit title\n");
  printf("4. Delete todo\n");
  printf("5. Save todos\n");
  printf("6. Load todos\n");
  printf("0. Exit\n");
  printf("Enter your choice: ");
}

int get_choice(void) {
  int choice;
  if (scanf("%d", &choice) != 1) {
    clear_stdin();
    return -1;
  }
  clear_stdin();
  return choice;
}
