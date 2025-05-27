#ifndef H_UI
#define H_UI

#include <stddef.h>

#include "todo.h"

typedef enum
{
  TUI_MENU_NOTHING = -1,
  TUI_MENU_ADD_TODO = 1,
  TUI_MENU_TOGGLE_STATUS = 2,
  TUI_MENU_EDIT_TITLE = 3,
  TUI_MENU_DELETE_TODO = 4,
  TUI_MENU_SAVE_TODOS = 5,
  TUI_MENU_LOAD_TODOS = 6,
  TUI_MENU_FILTER = 7,
  TUI_MENU_SORT = 8,
  TUI_MENU_EXIT = 0,
} TuiMenu;

typedef enum
{
  TIU_MENU_FILTER_NOTHING = -1,
  TUI_MENU_FILTER_DONE = 1,
  TUI_MENU_FILTER_NOT_DONE = 2,
  TUI_MENU_FILTER_ALL = 3,
  TUI_MENU_FILTER_EXIT = 0,
} TuiMenuFilter;

typedef enum
{
  TUI_MENU_SORT_NOTHING = -1,
  TUI_MENU_SORT_ID_ASC = 1,
  TUI_MENU_SORT_ID_DESC = 2,
  TUI_MENU_SORT_STATUS_ASC = 3,
  TUI_MENU_SORT_STATUS_DESC = 4,
  TUI_MENU_SORT_TITLE_ASC = 5,
  TUI_MENU_SORT_TITLE_DESC = 6,
  TUI_MENU_SORT_EXIT = 0,
} TuiMenuSort;

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

void tui_print_menus_fileter(void);

void tui_print_menus_sort(void);

void tui_print_todos(const TodoList *todos);

TuiResult tui_input_text(char *buf, int size, const char *prompt);

TuiResult tui_input_number(size_t *choise, const char *prompt);

void tui_normolized_stdin(void);

void tui_clear_screen(void);

#endif // H_UI
