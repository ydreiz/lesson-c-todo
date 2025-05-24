#ifndef H_UI
#define H_UI

#include <stddef.h>

#include "todo.h"

#define TUI_MENU_ADD_TODO 1
#define TUI_MENU_TOGGLE_STATUS 2
#define TUI_MENU_EDIT_TITLE 3
#define TUI_MENU_DELETE_TODO 4
#define TUI_MENU_SAVE_TODOS 5
#define TUI_MENU_LOAD_TODOS 6
#define TUI_MENU_EXIT 0

typedef enum
{
  TUI_NOTHING = -1,
  TUI_OK = 0,
  TUI_ERR_INVALID_INPUT = 101,
  TUI_ERR_EMPTY_INPUT = 102,
  TUI_CHOSE_AGREE = 201,
  TUI_CHOSE_REJECT = 202,
} TuiResult;

void tui_print_menus(void);

void tui_print_todos(const Todo todos[], size_t count);

TuiResult tui_input_text(char *buf, int size, const char *prompt);

TuiResult tui_input_number(size_t *choise, const char *prompt);

void tui_normolized_stdin(void);

#endif // H_UI
