#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "tui.h"
#include "utils.h"

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

  size_t max_title_len = 0;
  for (size_t i = 0; i < todos->size; i++)
  {
    size_t len = strlen(todos->data[i].title);
    if (max_title_len < len)
    {
      max_title_len = len;
    }
  }
  size_t id_width = snprintf(NULL, 0, "%lu", todos->next_id - 1);
  printf("\n");
  for (size_t i = 0; i < todos->size; i++)
  {
    Todo todo = todos->data[i];
    char *status_str = todo.done ? "[x]" : "[ ]";
    printf("[%*lu] %-*s %s\n", (int)id_width, todo.id, (int)max_title_len, todo.title, status_str);
  }
  printf("Total todos: %lu\n", todos->size);
}

TuiResult tui_input_text(u_string *buf, int size, const char *prompt)
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
  char buf[128];
  TuiResult res = tui_input_text(buf, sizeof(buf), prompt);
  if (res != TUI_OK)
  {
    return res;
  }

  char *endptr;
  long val = strtol(buf, &endptr, 10);
  if (*endptr != '\0' || endptr == buf || val < 0)
  {
    return TUI_ERR_INVALID_INPUT;
  }

  *choice = (size_t)val;
  return TUI_OK;
}

void tui_normolized_stdin()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void tui_clear_screen()
{
#ifdef _WIN32
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD cellCount;
  DWORD count;
  COORD homeCoords = {0, 0};
  if (hOut == INVALID_HANDLE_VALUE)
    return;
  if (!GetConsoleScreenBufferInfo(hOut, &csbi))
  {
    return;
  }
  cellCount = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter(hOut, (TCHAR)' ', cellCount, homeCoords, &count);
  FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
  SetConsoleCursorPosition(hOut, homeCoords);
#else
  printf("\033[H\033[J");
#endif
}
