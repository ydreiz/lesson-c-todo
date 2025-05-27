#include <stdio.h>
#include <string.h>

#include "todo.h"
#include "tui.h"

void tui_print_menus(void)
{
  printf("\nMenu:\n");
  printf("1. Add todo\n");
  printf("2. Toggle todo status\n");
  printf("3. Edit title\n");
  printf("4. Delete todo\n");
  printf("5. Filter todos\n");
  printf("6. Sort todos\n");
  printf("7. Save todos\n");
  printf("8. Load todos\n");
  printf("0. Exit\n");
  printf("Enter your choice: ");
}

void tui_print_menus_fileter(void)
{
  printf("\nFilter by:\n");
  printf("1. Status (Done)\n");
  printf("2. Status (Not done)\n");
  printf("3. Show all todos\n");
  printf("0. Back to main menu\n");
  printf("Enter your choice: ");
}

void tui_print_menus_sort(void)
{
  printf("\nSort by:\n");
  printf("1. ID (asc)\n");
  printf("2. ID (desc)\n");
  printf("3. Status (asc)\n");
  printf("4. Status (desc)\n");
  printf("5. Title (asc)\n");
  printf("6. Title (desc)\n");
  printf("0. Back to main menu\n");
  printf("Enter your choice: ");
}

void tui_print_todos(const TodoList *todos)
{
  if (todos == NULL || todos->size == 0)
  {
    return;
  }

  printf("\n");
  for (size_t i = 0; i < todos->size; i++)
  {
    Todo todo = todos->data[i];
    char *status_str = todo.done ? "[x]" : "[ ]";

    if (todos->next_id < 10)
    {
      printf("[%lu] %-50s %s\n", todo.id, todo.title, status_str);
    }
    else if (todos->next_id >= 100)
    {
      printf("[%3lu] %-48s %s\n", todo.id, todo.title, status_str);
    }
    else
    {
      printf("[%2lu] %-49s %s\n", todo.id, todo.title, status_str);
    }
  }

  printf("Total todos: %lu\n", todos->size);
}

TuiResult tui_input_text(char *buf, int size, const char *prompt)
{
  if (prompt != NULL)
  {
    printf("%s", prompt);
  }

  if (fgets(buf, size, stdin) == NULL)
  {
    return TUI_ERR_INVALID_INPUT;
  }
  else if (ferror(stdin))
  {
    return TUI_ERR_INVALID_INPUT;
  }

  buf[strcspn(buf, "\n")] = '\0';

  return strlen(buf) > 0 ? TUI_OK : TUI_ERR_EMPTY_INPUT;
}

TuiResult tui_input_number(size_t *choice, const char *prompt)
{
  if (prompt != NULL)
  {
    printf("%s", prompt);
  }

  if (scanf("%lu", choice) != 1)
  {
    tui_normolized_stdin();

    return TUI_ERR_INVALID_INPUT;
  }

  tui_normolized_stdin();

  return TUI_OK;
}

void tui_normolized_stdin()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void tui_clear_screen() { printf("\033[H\033[J"); }
