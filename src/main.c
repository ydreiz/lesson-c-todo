#include "todo.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int global_id = 0;

int main(void) {
  Todo todos[MAX_TODOS];
  int count = 0;

  count = load_todos("todos.txt", todos, MAX_TODOS);

  for (int i = 0; i < count; i++) {
    if (todos[i].id > global_id)
      global_id = todos[i].id;
  }

  int running = 1;
  while (running) {
    print_todos(todos, count);
    print_menu();

    int choice = get_choice();
    switch (choice) {
    case 1:
      count = add_todo(todos, MAX_TODOS, count, &global_id);
      break;
    case 2: {
      unsigned int id;
      printf("Enter todo ID to toggle status: ");
      if (scanf("%u", &id) == 1) {
        toggle_todo_status(todos, count, id);
        clear_stdin();
      }
      break;
    }
    case 3: {
      unsigned int id;
      printf("Enter todo ID to edit title: ");
      if (scanf("%u", &id) == 1) {
        clear_stdin();
        edit_todo_title(todos, count, id);
      }
      break;
    }
    case 4: {
      unsigned int id;
      printf("Enter todo ID to delete: ");
      if (scanf("%u", &id) == 1) {
        delete_todo(todos, &count, id);
        clear_stdin();
      }
      break;
    }
    case 5:
      if (save_todos("todos.txt", todos, count)) {
        printf("Todos saved successfully.\n");
      } else {
        printf("Error saving todos.\n");
      }
      break;
    case 6:
      count = load_todos("todos.txt", todos, MAX_TODOS);
      printf("Todos loaded.\n");
      break;
    case 0:
      running = 0;
      break;
    default:
      printf("Invalid choice.\n");
      break;
    }
  }

  return EXIT_SUCCESS;
}
