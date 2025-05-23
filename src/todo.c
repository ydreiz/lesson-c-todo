#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

void clear_stdin(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

const char *status_str(bool ch) { return ch ? "[x]" : "[ ]"; }

TodoResult input_title(char *buf, int size, const char *prompt) {
  printf("%s: ", prompt);
  if (fgets(buf, size, stdin) == NULL) {
    return TODO_ERR_INVALID_INPUT;
  } else if (ferror(stdin)) {
    return TODO_ERR_INVALID_INPUT;
  }

  buf[strcspn(buf, "\n")] = '\0';

  return strlen(buf) > 0 ? TODO_OK : TODO_ERR_EMPTY_INPUT;
}

TodoResult input_status() {
  char ch[2];
  do {
    printf("Status is done [y/n] (Default: n): ");
    if (fgets(ch, sizeof(ch), stdin) == NULL) {
      return TODO_ERR_INVALID_INPUT;
    } else if (ferror(stdin)) {
      return TODO_ERR_INVALID_INPUT;
    }
    ch[strcspn(ch, "\n")] = '\0';

    if (ch[0] == '\0') {
      strcpy(ch, "n");
    } else if (ch[strlen(ch) - 1] != '\n') {
      clear_stdin();
    }

    if (strcmp(ch, "y") || strcmp(ch, "n")) {
      return strcmp(ch, "y") == 0 ? TODO_CHOSE_AGREE : TODO_CHOSE_REJECT;
    }
  } while (true);
}

TodoResult add_todo(Todo **todos, size_t *count, size_t *global_id,
                    size_t *capacity) {
  char title[TITLE_SIZE];
  TodoResult result = input_title(title, sizeof(title), "New todo title");
  if (result == TODO_ERR_INVALID_INPUT) {
    return TODO_ERR_INVALID_INPUT;
  }
  if (result == TODO_ERR_EMPTY_INPUT) {
    return TODO_ERR_EMPTY_INPUT;
  }

  Todo todo;
  todo.done = input_status();
  todo.id = ++(*global_id);
  strcpy(todo.title, title);

  if (*count == *capacity) {
    *capacity *= 2;
    Todo *tmp = realloc(*todos, *capacity * sizeof(Todo));
    if (!tmp) {
      return TODO_ERR_ALLOC;
    }
    *todos = tmp;
  }
  (*todos)[*count] = todo;

  (*count)++;

  return TODO_OK;
}

TodoResult delete_todo(Todo todos[], size_t *count, size_t id) {
  int pos = -1;
  for (size_t i = 0; i < *count; i++) {
    if (todos[i].id == id) {
      pos = i;
      break;
    }
  }

  if (pos == -1) {
    return TODO_ERR_NOT_FOUND;
  }

  for (size_t i = pos; i < *count - 1; i++) {
    todos[i] = todos[i + 1];
  }

  (*count)--;

  return TODO_OK;
}

TodoResult toggle_todo_status(Todo todos[], size_t count, size_t id) {
  for (size_t i = 0; i < count; i++) {
    if (todos[i].id == id) {
      todos[i].done = !todos[i].done;
      return TODO_OK;
    }
  }
  return TODO_ERR_NOT_FOUND;
}

TodoResult edit_todo_title(Todo todos[], size_t count, size_t id) {
  int pos = -1;
  for (size_t i = 0; i < count; i++) {
    if (id == todos[i].id) {
      pos = i;
      break;
    }
  }

  if (pos == -1) {
    return TODO_ERR_NOT_FOUND;
  }

  char title[TITLE_SIZE];
  TodoResult result;
  result = input_title(title, sizeof(title), "New todo title");
  if (result == TODO_ERR_INVALID_INPUT) {
    return TODO_ERR_INVALID_INPUT;
  }
  if (result == TODO_ERR_EMPTY_INPUT) {
    return TODO_ERR_EMPTY_INPUT;
  }

  strcpy(todos[pos].title, title);

  return TODO_OK;
}

void print_todos(const Todo todos[], size_t count) {
  for (size_t i = 0; i < count; i++) {
    Todo todo = todos[i];
    if (count < 10) {
      printf("[%lu] %-50s %s\n", todo.id, todo.title, status_str(todo.done));
    } else if (count >= 100) {
      printf("[%3lu] %-48s %s\n", todo.id, todo.title, status_str(todo.done));
    } else {
      printf("[%2lu] %-49s %s\n", todo.id, todo.title, status_str(todo.done));
    }
  }
  printf("Total todos: %lu\n", count);
}
