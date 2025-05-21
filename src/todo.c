#include "todo.h"
#include <stdio.h>
#include <string.h>

void clear_stdin(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

const char *status_str(bool ch) { return ch ? "[x]" : "[ ]"; }

bool input_title(char *buf, int size, const char *prompt) {
  printf("%s: ", prompt);
  if (fgets(buf, size, stdin) == NULL) {
    printf("Error when enter title!\n");
    return false;
  }
  buf[strcspn(buf, "\n")] = '\0';

  return strlen(buf) > 0;
}

bool input_status() {
  char ch[2];
  do {
    printf("Status is done [y/n] (Default: n): ");
    if (fgets(ch, sizeof(ch), stdin) == NULL) {
      printf("Error when read status!\n");
      return false;
    }
    ch[strcspn(ch, "\n")] = '\0';

    if (ch[0] == '\0') {
      strcpy(ch, "n");
    } else if (ch[strlen(ch) - 1] != '\n') {
      clear_stdin();
    }

    if (strcmp(ch, "y") || strcmp(ch, "n")) {
      return strcmp(ch, "y") == 0;
    }
  } while (true);
}

int add_todo(Todo todos[], int capacity, int count, unsigned int *gloab_id) {
  if (capacity == count) {
    printf("Todos list overflow, before add new todo, remove some todo!\n");
    return count;
  }

  char title[TITLE_SIZE];
  if (!input_title(title, sizeof(title), "New todo title")) {
    return count;
  }

  Todo todo;
  todo.done = input_status();
  todo.id = ++(*gloab_id);
  strcpy(todo.title, title);

  todos[count] = todo;
  return count + 1;
}

bool delete_todo(Todo todos[], int *count, unsigned int id) {
  int pos = -1;
  for (int i = 0; i < *count; i++) {
    if (todos[i].id == id) {
      pos = i;
      break;
    }
  }

  if (pos == -1) {
    return false;
  }

  for (int i = pos; i < *count - 1; i++) {
    todos[i] = todos[i + 1];
  }
  (*count)--;
  return true;
}

bool toggle_todo_status(Todo todos[], int count, unsigned int id) {
  for (int i = 0; i < count; i++) {
    if (todos[i].id == id) {
      todos[i].done = !todos[i].done;
      return true;
    }
  }
  return false;
}

bool edit_todo_title(Todo todos[], int count, unsigned int id) {
  int pos = -1;
  for (int i = 0; i < count; i++) {
    if (id == todos[i].id) {
      pos = i;
      break;
    }
  }

  if (pos == -1) {
    fprintf(stderr, "Todo with ID %d not found!\n", id);
    return false;
  }

  char title[TITLE_SIZE];
  if (!input_title(title, sizeof(title), "Enter new title")) {
    printf("The title has not been changed because"
           " you have not entered a new one.\n");
    return false;
  }
  strcpy(todos[pos].title, title);
  printf("The headline has been successfully changed!\n");
  return true;
}

void print_todos(const Todo todos[], int count) {
  for (int i = 0; i < count; i++) {
    Todo todo = todos[i];
    if (count < 10) {
      printf("[%d] %-50s %s\n", todo.id, todo.title, status_str(todo.done));
    } else if (count >= 100) {
      printf("[%3d] %-48s %s\n", todo.id, todo.title, status_str(todo.done));
    } else {
      printf("[%2d] %-49s %s\n", todo.id, todo.title, status_str(todo.done));
    }
  }
  printf("Total todos: %d\n", count);
}
