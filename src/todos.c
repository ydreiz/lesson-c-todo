#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "todo.h"
#include "tui.h"

size_t global_id = 0;
const size_t initial_capacity = 3;
size_t capacity = initial_capacity;

void recalculate_global_id(const Todo *todos, size_t count)
{
  if (todos == NULL || count == 0)
  {
    return;
  }

  for (size_t i = 0; i < count; i++)
  {
    if (todos[i].id > global_id)
      global_id = todos[i].id;
  }
}

int main(void)
{
  Todo *todos = malloc(initial_capacity * sizeof(Todo));
  if (!todos)
  {
    print_error("Failed to allocate memory for todos.");
    return EXIT_FAILURE;
  }

  size_t count = 0;
  TuiResult tui_result = TUI_OK;
  TodoResult todo_result = todo_load(TODO_FILE, &todos, &capacity, &count);

  if (todo_result == TODO_ERR_ALLOC)
  {
    print_error("Unable to allocate required memory. Operation aborted.");

    free(todos);

    return EXIT_FAILURE;
  }
  else if (todo_result == TODO_ERR_FILE)
  {
    print_error("Unable to open file.");
  }
  else
  {
    recalculate_global_id(todos, count);
  }

  int running = 1;
  while (running)
  {
    TodoResult todo_result = TODO_NOTHING;

    tui_print_todos(todos, count);
    tui_print_menus();

    size_t choice = TUI_MENU_EXIT;
    tui_result = tui_input_number(&choice, NULL);
    switch (choice)
    {
    case TUI_MENU_ADD_TODO:
    {
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
      if (tui_input_text(status_str, count, "Is done? [y/N]: ") == TUI_ERR_EMPTY_INPUT)
      {
        strcpy(status_str, "n");
      }

      if ((todo_result = todo_add(title, *status_str == 'y', &todos, &count, &global_id, &capacity)) == TODO_OK)
      {
        print_success("Todo has been added successfully.");
        continue;
      }

      break;
    }
    case TUI_MENU_TOGGLE_STATUS:
    {
      size_t id = 0;
      if ((tui_result = tui_input_number(&id, "Enter ID to toggle status: ")) != TUI_OK)
      {
        continue;
      }

      size_t pos = -1;
      if ((todo_result = todo_find(todos, count, id, &pos)) == TODO_OK)
      {
        if ((todo_result = todo_toggle_status(todos, pos)) == TODO_OK)
        {
          print_success("Status has been changed.");
          continue;
        }
      }
      break;
    }
    case TUI_MENU_EDIT_TITLE:
    {
      size_t id = 0;
      if ((tui_result = tui_input_number(&id, "Enter ID to edit todo: ")) != TUI_OK)
      {
        continue;
      }

      size_t pos = -1;
      if ((todo_result = todo_find(todos, count, id, &pos)) == TODO_OK)
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
      if ((todo_result = todo_find(todos, count, id, &pos)) == TODO_OK)
      {
        if ((todo_result = todo_delete(todos, &count, pos)) == TODO_OK)
        {
          print_success("Todo deleted successfully.");
          continue;
        }
      }
      break;
    }
    case TUI_MENU_SAVE_TODOS:
    {
      if ((todo_result = todo_save(TODO_FILE, todos, count)) == TODO_OK)
      {
        print_success("Todos saved successfully.");
        continue;
      }
      break;
    }
    case TUI_MENU_LOAD_TODOS:
    {
      count = 0;
      capacity = initial_capacity;
      free(todos);
      todos = malloc(initial_capacity * sizeof(Todo));
      if (!todos)
      {
        print_error("Failed to allocate memory for todos.");
        return EXIT_FAILURE;
      }

      if ((todo_result = todo_load(TODO_FILE, &todos, &capacity, &count)) == TODO_OK)
      {
        print_success("Todos loaded successfully.");
        continue;
      }

      break;
    }
    case TUI_MENU_EXIT:
    {
      running = 0;
      break;
    }
    }

    if (todo_result == TODO_ERR_ALLOC)
    {
      free(todos);
      print_error("Unable to allocate required memory. Operation aborted.");
      return EXIT_FAILURE;
    }
    else if (todo_result == TODO_ERR_NOT_FOUND)
    {
      print_error("Todo could not be found.");
    }
    else if (todo_result == TODO_ERR_OUT_OF_BOUNDS)
    {
      print_error("Todo ID is out of bounds.");
    }
    else if (todo_result == TODO_ERR_EMPTY)
    {
      print_error("Todo list is empty.");
    }
    else if (todo_result == TODO_ERR_FILE)
    {
      print_error("Unable to close file.");
    }
    else if (todo_result == TODO_OK)
    {
      print_success("Operation completed successfully.");
    }
  }

  free(todos);

  return EXIT_SUCCESS;
}
