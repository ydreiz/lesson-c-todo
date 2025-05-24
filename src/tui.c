#include <stdio.h>
#include <string.h>

#include "todo.h"
#include "tui.h"

void tui_print_menus(void) {
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

void tui_print_todos(const Todo todos[], size_t count) {
  for (size_t i = 0; i < count; i++) {
    Todo todo = todos[i];
    char *status_str = todo.done ? "[x]" : "[ ]";

    if (count < 10) {
      printf("[%lu] %-50s %s\n", todo.id, todo.title, status_str);
    } else if (count >= 100) {
      printf("[%3lu] %-48s %s\n", todo.id, todo.title, status_str);
    } else {
      printf("[%2lu] %-49s %s\n", todo.id, todo.title, status_str);
    }
  }

  printf("Total todos: %lu\n", count);
}

TuiResult tui_input_text(char *buf, int size, const char *prompt) {
  if (prompt != NULL) {
    printf("%s", prompt);
  }

  if (fgets(buf, size, stdin) == NULL) {
    return TUI_ERR_INVALID_INPUT;
  } else if (ferror(stdin)) {
    return TUI_ERR_INVALID_INPUT;
  }

  buf[strcspn(buf, "\n")] = '\0';

  return strlen(buf) > 0 ? TUI_OK : TUI_ERR_EMPTY_INPUT;
}

TuiResult tui_input_number(size_t *choice, const char *prompt) {
  if (prompt != NULL) {
    printf("%s", prompt);
  }

  if (scanf("%lu", choice) != 1) {
    tui_normolized_stdin();

    return TUI_ERR_INVALID_INPUT;
  }

  tui_normolized_stdin();

  return TUI_OK;
}

void tui_normolized_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
