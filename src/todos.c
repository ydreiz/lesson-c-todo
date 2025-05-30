#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "print.h"
#include "todo_list.h"
#include "todo_store_simple.h"
#include "tui.h"

void screen_todo_add(TodoList *todos, TodoResult *todo_result);
void screen_todo_togggle_status(TodoList *todos, TodoResult *todo_result);
void screen_todo_change_title(TodoList *todos, TodoResult *todo_result);
void screen_todo_delete(TodoList *todos, TodoResult *todo_result);
void screen_todo_filter(const TodoList *todos);
void screen_todo_sort(TodoList *todos);
void screen_todo_save(TodoList *todos, TodoResult *todo_result);
void screen_todo_load(TodoList **todos, TodoResult *todo_result);

int main(void)
{
  tui_clear_screen();

  TodoList *todos = todo_list_create(INITIAL_CAPACITY);
  if (!todos || !todos->data)
  {
    p_error("Failed to allocate memory for todos");
    return EXIT_FAILURE;
  }

  TuiResult tui_result = TUI_OK;
  TodoResult todo_result = todo_load(TODO_FILE, todos);
  if (todo_result == TODO_ERR_ALLOC)
  {
    p_error("Unable to allocate required memory. Operation aborted");
    todo_list_free(&todos);
    return EXIT_FAILURE;
  }
  else if (todo_result == TODO_ERR_FILE)
  {
    print_notify("Unable to open 'todos.txt' file");
  }
  else
  {
    todo_list_recalculate_next_id(todos);
  }

  int running = 1;
  size_t choice = TUI_MENU_EXIT;
  while (running)
  {
    TodoResult todo_result = TODO_NOTHING;

    tui_clear_screen();
    tui_print_todos(todos);
    tui_print_menus();

    tui_result = tui_input_number(&choice, NULL);
    switch (choice)
    {
    case TUI_MENU_ADD_TODO:
      screen_todo_add(todos, &todo_result);
      break;
    case TUI_MENU_TOGGLE_STATUS:
      screen_todo_togggle_status(todos, &todo_result);
      break;
    case TUI_MENU_EDIT_TITLE:
      screen_todo_change_title(todos, &todo_result);
      break;
    case TUI_MENU_DELETE_TODO:
      screen_todo_delete(todos, &todo_result);
      break;
    case TUI_MENU_FILTER:
      screen_todo_filter(todos);
      break;
    case TUI_MENU_SORT:
      screen_todo_sort(todos);
      break;
    case TUI_MENU_SAVE_TODOS:
      screen_todo_save(todos, &todo_result);
      break;
    case TUI_MENU_LOAD_TODOS:
      screen_todo_load(&todos, &todo_result);
      break;
    case TUI_MENU_EXIT:
      running = 0;
      break;
    }

    if (todo_result == TODO_ERR_ALLOC)
    {
      p_error("Unable to allocate required memory. Operation aborted.");
      exit(EXIT_FAILURE);
    }
    else if (todo_result == TODO_ERR_NOT_FOUND)
    {
      print_notify("Todo could not be found.");
    }
    else if (todo_result == TODO_ERR_OUT_OF_BOUNDS)
    {
      print_notify("Todo ID is out of bounds.");
    }
    else if (todo_result == TODO_ERR_EMPTY)
    {
      print_notify("Todo list is empty.");
    }
    else if (todo_result == TODO_ERR_FILE)
    {
      print_notify("Unable to open 'todos.txt' file");
    }
    else if (todo_result == TODO_OK)
    {
      print_success("Operation completed successfully.");
    }
  }

  todo_list_free(&todos);
  tui_clear_screen();

  return EXIT_SUCCESS;
}
