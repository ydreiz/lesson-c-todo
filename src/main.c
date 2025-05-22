#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "todo.h"
#include "ui.h"

size_t global_id = 0;
const size_t initial_capacity = 3;
size_t capacity = initial_capacity;

int main(void) {
  Todo *todos = malloc(initial_capacity * sizeof(Todo));
  if (!todos) {
    fprintf(stderr, "Failed to allocate memory for todos\n");
    return EXIT_FAILURE;
  }
  int count = 0;

  count = load_todos(TODO_PATH, &todos, &capacity);

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
      count = add_todo(&todos, count, &global_id, &capacity);
      break;
    case 2: {
      size_t id;
      printf("Enter todo ID to toggle status: ");
      if (scanf("%lu", &id) == 1) {
        toggle_todo_status(todos, count, id);
        clear_stdin();
      }
      break;
    }
    case 3: {
      size_t id;
      printf("Enter todo ID to edit title: ");
      if (scanf("%lu", &id) == 1) {
        clear_stdin();
        edit_todo_title(todos, count, id);
      }
      break;
    }
    case 4: {
      size_t id;
      printf("Enter todo ID to delete: ");
      if (scanf("%lu", &id) == 1) {
        delete_todo(todos, &count, id);
        clear_stdin();
      }
      break;
    }
    case 5:
      if (save_todos(TODO_PATH, todos, count)) {
        printf("Todos saved successfully.\n");
      } else {
        printf("Error saving todos.\n");
      }
      break;
    case 6:
      count = load_todos(TODO_PATH, &todos, &capacity);
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

  free(todos);

  return EXIT_SUCCESS;
}
