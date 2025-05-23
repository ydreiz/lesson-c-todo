#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "todo.h"
#include "ui.h"

size_t global_id = 0;
const size_t initial_capacity = 3;
size_t capacity = initial_capacity;

int main(void) {
  Todo *todos = malloc(initial_capacity * sizeof(Todo));
  if (!todos) {
    print_error("Failed to allocate memory for todos.");
    return EXIT_FAILURE;
  }
  size_t count = 0;
  TodoResult result = -1;

  result = load_todos(TODO_PATH, &todos, &capacity, &count);
  if (result == TODO_ERR_ALLOC) {
    print_error("Unable to allocate required memory. Operation aborted.");
    return EXIT_FAILURE;
  } else if (result == TODO_ERR_FILE) {
    print_error("Unable to open file.");
    free(todos);
    return EXIT_FAILURE;
  }

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
      result = add_todo(&todos, &count, &global_id, &capacity);
      if (result == TODO_OK) {
        print_success("The todo has been added.");
      }
      break;
    case 2: {
      size_t id;
      printf("Enter todo ID to toggle status: ");
      if (scanf("%lu", &id) == 1) {
        result = toggle_todo_status(todos, count, id);
        if (result == TODO_OK) {
          print_success("Status has been changed.");
        }
        clear_stdin();
      }
      break;
    }
    case 3: {
      size_t id;
      printf("Enter todo ID to edit title: ");
      if (scanf("%lu", &id) == 1) {
        clear_stdin();
        result = edit_todo_title(todos, count, id);
        if (result == TODO_OK) {
          print_success("Title has been changed.");
        } else if (result == TODO_ERR_EMPTY_INPUT) {
          print_notify("Title unchanged due to empty input.");
        }
      }
      break;
    }
    case 4: {
      size_t id;
      printf("Enter todo ID to delete: ");
      if (scanf("%lu", &id) == 1) {
        result = delete_todo(todos, &count, id);
        if (result == TODO_OK) {
          print_success("Todo deleted successfully.");
        }
        clear_stdin();
      }
      break;
    }
    case 5:
      result = save_todos(TODO_PATH, todos, &count);
      if (result == TODO_OK) {
        print_success("Todos have been saved.");
      }
      break;
    case 6:
      result = load_todos(TODO_PATH, &todos, &capacity, &count);
      if (result == TODO_OK) {
        print_success("Todos have been loaded.");
      }
      break;
    case 0:
      running = 0;
      break;
    default:
      print_notify("Invalid choice.");
      break;
    }

    if (result == TODO_ERR_ALLOC) {
      print_error("Unable to allocate required memory. Operation aborted.");
      break;
    } else if (result == TODO_ERR_INVALID_INPUT) {
      print_error("Text input error. Please try again.");
    } else if (result == TODO_ERR_NOT_FOUND) {
      print_error("Todo could not be found.");
    } else if (result == TODO_ERR_FILE) {
      print_error("Unable to open file.");
    }
  }

  free(todos);

  return EXIT_SUCCESS;
}
