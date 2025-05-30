#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "print.h"
#include "todo.h"
#include "todo_common.h"
#include "todo_filter.h"
#include "todo_list.h"
#include "todo_sort.h"
#include "todo_store_simple.h"
#include "tui.h"
#include "utils.h"

void screen_todo_add(TodoList *todos, TodoResult *todo_result)
{
  u_string title[100];
  TuiResult tui_result = tui_input_text(title, sizeof(title), "Enter title: ");
  if (tui_result == TUI_ERR_INVALID_INPUT)
  {
    print_notify("Invalid input. Please try again.");
  }
  else if (tui_result == TUI_ERR_EMPTY_INPUT)
  {
    print_notify("Record not added as no title was entered.");
    return;
  }

  u_string status_str[2];
  if (tui_input_text(status_str, 2, "Is done? [y/N]: ") == TUI_ERR_EMPTY_INPUT)
  {
    strcpy(status_str, "n");
  }

  if (((*todo_result) = todo_add(title, *status_str == 'y', todos)) == TODO_OK)
  {
    print_success("Todo has been added successfully.");
  }
}

void screen_todo_togggle_status(TodoList *todos, TodoResult *todo_result)
{
  size_t id = 0;
  if (tui_input_number(&id, "Enter ID to toggle status: ") != TUI_OK)
  {
    return;
  }
  size_t pos = -1;
  if (((*todo_result) = todo_find_idx(todos, id, &pos)) == TODO_OK)
  {
    if (((*todo_result) = todo_toggle_status(todos, pos)) == TODO_OK)
    {
      print_success("Status has been changed.");
    }
  }
}

void screen_todo_change_title(TodoList *todos, TodoResult *todo_result)
{
  TuiResult tui_result;
  size_t todo_id = 0;
  if ((tui_result = tui_input_number(&todo_id, "Enter ID to edit todo: ")) != TUI_OK)
  {
    return;
  }
  size_t todo_position = -1;
  if (((*todo_result) = todo_find_idx(todos, todo_id, &todo_position)) == TODO_OK)
  {
    char title[100];
    tui_result = tui_input_text(title, sizeof(title), "Enter title: ");
    if (tui_result == TUI_OK)
    {
      if (((*todo_result) = todo_change_title(title, todos, todo_position)) == TODO_OK)
      {
        print_success("Title has been changed.");
      }
    }
    else if (tui_result == TUI_ERR_EMPTY_INPUT)
    {
      print_notify("Title unchanged due to empty input.");
    }
  }
}

void screen_todo_delete(TodoList *todos, TodoResult *todo_result)
{
  size_t todo_id = 0;
  if (tui_input_number(&todo_id, "Enter ID to delete todo: ") != TUI_OK)
  {
    return;
  }
  (*todo_result) = todo_list_delete(todos, todo_id);
}

void screen_todo_filter(const TodoList *todos)
{
  TodoList *todos_filtered = todo_list_create(INITIAL_CAPACITY);
  if (!todos_filtered || !todos_filtered->data)
  {
    p_error("Failed to allocate memory for filtered todos");
    exit(EXIT_FAILURE);
  }

  int filter_running = 1;
  size_t filter_choice = TIU_MENU_FILTER_NOTHING;
  while (filter_running)
  {
    tui_clear_screen();
    tui_print_todos(todos_filtered->size ? todos_filtered : todos);
    tui_print_menus_fileter();

    tui_input_number(&filter_choice, NULL);
    switch (filter_choice)
    {
    case TUI_MENU_FILTER_DONE:
      todo_list_filter(todo_is_done, todos, todos_filtered);
      break;
    case TUI_MENU_FILTER_NOT_DONE:
      todo_list_filter(todo_is_not_done, todos, todos_filtered);
      break;
    case TUI_MENU_FILTER_ALL:
      todo_list_free(&todos_filtered);
      todos_filtered = todo_list_create(INITIAL_CAPACITY);
      if (!todos_filtered || !todos_filtered->data)
      {
        p_error("Failed to allocate memory for filtered todos.");
        exit(EXIT_FAILURE);
      }
      break;
    case TUI_MENU_FILTER_EXIT:
      filter_running = 0;
      break;
    }
  }
  todo_list_free(&todos_filtered);
}

void screen_todo_sort(TodoList *todos)
{
  int sort_running = 1;
  size_t sort_choice = TUI_MENU_SORT_NOTHING;
  while (sort_running)
  {
    tui_clear_screen();
    tui_print_todos(todos);
    tui_print_menus_sort();

    tui_input_number(&sort_choice, NULL);
    switch (sort_choice)
    {
    case TUI_MENU_SORT_ID_ASC:
      todo_list_sort(todo_compare_id_asc, todos);
      break;
    case TUI_MENU_SORT_ID_DESC:
      todo_list_sort(todo_compare_id_desc, todos);
      break;
    case TUI_MENU_SORT_STATUS_ASC:
      todo_list_sort(todo_compare_status_asc, todos);
      break;
    case TUI_MENU_SORT_STATUS_DESC:
      todo_list_sort(todo_compare_status_desc, todos);
      break;
    case TUI_MENU_SORT_TITLE_ASC:
      todo_list_sort(todo_compare_title_asc, todos);
      break;
    case TUI_MENU_SORT_TITLE_DESC:
      todo_list_sort(todo_compare_title_desc, todos);
      break;
    case TUI_MENU_SORT_EXIT:
      sort_running = 0;
      break;
    }
  }
}

void screen_todo_save(TodoList *todos, TodoResult *todo_result)
{
  if (((*todo_result) = todo_save(TODO_FILE, todos)) == TODO_OK)
  {
    print_success("Todos saved successfully.");
  }
}

void screen_todo_load(TodoList **todos, TodoResult *todo_result)
{
  todo_list_free(todos);
  (*todos) = todo_list_create(INITIAL_CAPACITY);
  if (!(*todos) || !(*todos)->data)
  {
    p_error("Failed to allocate memory for todos.");
    exit(EXIT_FAILURE);
  }
  if (((*todo_result) = todo_load(TODO_FILE, *todos)) == TODO_OK)
  {
    todo_list_recalculate_next_id(*todos);
    print_success("Todos loaded successfully.");
  }
}
