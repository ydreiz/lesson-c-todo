#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "print.h"
#include "todo.h"
#include "todo_filter.h"
#include "todo_sort.h"
#include "tui.h"

size_t global_id = 0;
const size_t initial_capacity = 3;
size_t capacity = initial_capacity;

int main(void)
{
  tui_clear_screen();

  TodoList *todos = todo_list_create(initial_capacity);
  if (!todos || !todos->data)
  {
    p_error("Failed to allocate memory for todos");
    return EXIT_FAILURE;
  }

  TodoList *todos_filtered = todo_list_create(initial_capacity);
  if (!todos_filtered || !todos_filtered->data)
  {
    p_error("Failed to allocate memory for filtered todos");
    todo_list_destroy(&todos);
    return EXIT_FAILURE;
  }

  TuiResult tui_result = TUI_OK;
  TodoResult todo_result = todo_load(TODO_FILE, todos);
  if (todo_result == TODO_ERR_ALLOC)
  {
    p_error("Unable to allocate required memory. Operation aborted");
    todo_list_destroy(&todos);
    todo_list_destroy(&todos_filtered);
    return EXIT_FAILURE;
  }
  else if (todo_result == TODO_ERR_FILE)
  {
    print_notify("Unable to open 'todos.txt' file");
  }
  else
  {
    todo_recalculate_next_id(todos);
  }

  int running = 1;
  size_t choice = TUI_MENU_EXIT;
  while (running)
  {
    tui_clear_screen();

    TodoResult todo_result = TODO_NOTHING;

    tui_print_todos(todos);
    tui_print_menus();

    tui_result = tui_input_number(&choice, NULL);
    switch (choice)
    {
    case TUI_MENU_ADD_TODO:
      char title[100];
      tui_result = tui_input_text(title, sizeof(title), "Enter title: ");
      if (tui_result == TUI_ERR_INVALID_INPUT)
      {
        print_notify("Invalid input. Please try again.");
        continue;
      }
      else if (tui_result == TUI_ERR_EMPTY_INPUT)
      {
        print_notify("Record not added as no title was entered.");
        continue;
      }

      char status_str[2];
      if (tui_input_text(status_str, 2, "Is done? [y/N]: ") == TUI_ERR_EMPTY_INPUT)
      {
        strcpy(status_str, "n");
      }

      if ((todo_result = todo_add(title, *status_str == 'y', todos)) == TODO_OK)
      {
        print_success("Todo has been added successfully.");
        continue;
      }

      break;
    case TUI_MENU_TOGGLE_STATUS:
      size_t id = 0;
      if ((tui_result = tui_input_number(&id, "Enter ID to toggle status: ")) != TUI_OK)
      {
        continue;
      }

      size_t pos = -1;
      if ((todo_result = todo_find(todos, id, &pos)) == TODO_OK)
      {
        if ((todo_result = todo_toggle_status(todos, pos)) == TODO_OK)
        {
          print_success("Status has been changed.");
          continue;
        }
      }
      break;
    case TUI_MENU_EDIT_TITLE:
    {
      size_t id = 0;
      if ((tui_result = tui_input_number(&id, "Enter ID to edit todo: ")) != TUI_OK)
      {
        continue;
      }

      size_t pos = -1;
      if ((todo_result = todo_find(todos, id, &pos)) == TODO_OK)
      {
        char title[100];
        tui_result = tui_input_text(title, sizeof(title), "Enter title: ");
        if (tui_result == TUI_OK)
        {
          if ((todo_result = todo_change_title(title, todos, pos)) == TODO_OK)
          {
            print_success("Title has been changed.");
            continue;
          }
        }
        else if (tui_result == TUI_ERR_EMPTY_INPUT)
        {
          print_notify("Title unchanged due to empty input.");
          continue;
        }
      }

      break;
    }
    case TUI_MENU_DELETE_TODO:
    {
      size_t id = 0;
      if ((tui_result = tui_input_number(&id, "Enter ID to delete todo: ")) != TUI_OK)
      {
        continue;
      }

      size_t pos = -1;
      if ((todo_result = todo_find(todos, id, &pos)) == TODO_OK)
      {
        if ((todo_result = todo_delete(todos, pos)) == TODO_OK)
        {
          print_success("Todo deleted successfully.");
          continue;
        }
      }
      break;
    }
    case TUI_MENU_SAVE_TODOS:
      if ((todo_result = todo_save(TODO_FILE, todos)) == TODO_OK)
      {
        print_success("Todos saved successfully.");
        continue;
      }
      break;
    case TUI_MENU_LOAD_TODOS:
      todos->size = 0;
      todos->capacity = initial_capacity;
      todo_list_destroy(&todos);
      todo_list_destroy(&todos_filtered);
      todos = todo_list_create(initial_capacity);
      todos_filtered = todo_list_create(1);
      if (!todos || !todos->data || !todos_filtered || !todos_filtered->data)
      {
        p_error("Failed to allocate memory for todos.");
        return EXIT_FAILURE;
      }

      if ((todo_result = todo_load(TODO_FILE, todos)) == TODO_OK)
      {
        todo_recalculate_next_id(todos);
        print_success("Todos loaded successfully.");
        continue;
      }
      break;
    case TUI_MENU_FILTER:
    {
      TuiResult tui_result = TUI_OK;
      TodoResult todo_result = TODO_OK;

      int filter_running = 1;
      size_t filter_choice = TIU_MENU_FILTER_NOTHING;
      while (filter_running)
      {
        tui_clear_screen();
        tui_print_todos(todos_filtered->size ? todos_filtered : todos);
        tui_print_menus_fileter();

        tui_result = tui_input_number(&filter_choice, NULL);
        switch (filter_choice)
        {
        case TUI_MENU_FILTER_DONE:
          todo_result = todo_list_filter(todo_is_done, todos, todos_filtered);
          break;
        case TUI_MENU_FILTER_NOT_DONE:
          todo_result = todo_list_filter(todo_is_not_done, todos, todos_filtered);
          break;
        case TUI_MENU_FILTER_ALL:
          todo_list_destroy(&todos_filtered);
          todos_filtered = todo_list_create(initial_capacity);
          if (!todos_filtered || !todos_filtered->data)
          {
            p_error("Failed to allocate memory for filtered todos.");
            return EXIT_FAILURE;
          }
          break;
        case TUI_MENU_FILTER_EXIT:
          filter_running = 0;
          break;
        }
      }
      break;
    }
    case TUI_MENU_SORT:
    {
      TuiResult tui_result = TUI_OK;

      int sort_running = 1;
      size_t sort_choice = TUI_MENU_SORT_NOTHING;
      while (sort_running)
      {
        tui_clear_screen();
        tui_print_todos(todos);
        tui_print_menus_sort();

        tui_result = tui_input_number(&sort_choice, NULL);
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
      break;
    }
    case TUI_MENU_EXIT:
      running = 0;
      break;
    }

    if (todo_result == TODO_ERR_ALLOC)
    {
      p_error("Unable to allocate required memory. Operation aborted.");
      return EXIT_FAILURE;
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

  todo_list_destroy(&todos);
  todo_list_destroy(&todos_filtered);
  tui_clear_screen();

  return EXIT_SUCCESS;
}
