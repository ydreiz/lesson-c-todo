#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "todo.h"

void _fill_stub_todos(TodoList *todos, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    todo_add("", (i % 2 ? true : false), todos);
    snprintf(todos->data[i].title, sizeof(todos->data[i].title), "TEST %lu", todos->next_id - 1);
  }
}

bool test_todos_list_create(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);
  ASSERT_TRUE(todos->size == 0);
  ASSERT_TRUE(todos->next_id == 1);
  ASSERT_TRUE(todos->capacity == 3);

  todo_list_destroy(&todos);
  return true;
}

bool test_todos_list_create_null(void)
{
  TodoList *todos = todo_list_create(0);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->size == 0);
  ASSERT_TRUE(todos->next_id == 1);
  ASSERT_TRUE(todos->capacity == 0);

  todo_list_destroy(&todos);
  return true;
}

bool test_todos_list_create_failure(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  // Force realloc failure by setting capacity to 0
  todos->capacity = 0;
  TodoResult res = todo_list_resize(todos);

  ASSERT_TRUE(res == TODO_ERR_ALLOC);

  todo_list_destroy(&todos);
  return true;
}

bool test_todos_list_filtered_done(void)
{
  TodoList *todos = todo_list_create(100);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 100);

  TodoList *filtered_todos = todo_list_create(50);
  if (!filtered_todos || !filtered_todos->data)
  {
    todo_list_destroy(&todos);
    todo_list_destroy(&filtered_todos);
    return false;
  }

  TodoResult res = todo_list_filter(todos, filtered_todos, true);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(filtered_todos->size == 50); // 50 todos should be done

  todo_list_destroy(&todos);
  todo_list_destroy(&filtered_todos);
  return true;
}

bool test_todos_list_filtered_done_empty(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  todos->size = 0; // Empty list

  TodoList *filtered_todos = todo_list_create(1);
  if (!filtered_todos || !filtered_todos->data)
  {
    todo_list_destroy(&todos);
    todo_list_destroy(&filtered_todos);
    return false;
  }

  TodoResult res = todo_list_filter(todos, filtered_todos, true);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(filtered_todos->size == 0); // No todos should be done

  todo_list_destroy(&todos);
  todo_list_destroy(&filtered_todos);
  return true;
}

bool test_todos_list_filtered_done_null(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  todos->size = 0; // Empty list

  TodoList *filtered_todos = NULL; // Null pointer

  TodoResult res = todo_list_filter(todos, filtered_todos, true);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_destroy(&todos);
  return true;
}

bool test_add_todo_increases_count(void)
{
  TodoList *todos = todo_list_create(2);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  TodoResult res = todo_add("TEST TODO NAME", true, todos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->size == 1);
  ASSERT_TRUE(todos->next_id == 2);

  ASSERT_TRUE(strlen(todos->data[0].title) > 0);
  ASSERT_TRUE(strcmp(todos->data[0].title, "TEST TODO NAME") == 0);
  ASSERT_TRUE(todos->data[0].done == true);

  todo_list_destroy(&todos);
  return true;
}

bool test_add_todo_failure_realloc(void)
{
  TodoList *todos = todo_list_create(0); // Set capacity to 0 to force realloc failure
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  TodoResult res = todo_add("TEST TODO NAME", true, todos);

  ASSERT_TRUE(res == TODO_ERR_ALLOC);

  todo_list_destroy(&todos);
  return true;
}

bool test_find_todo_by_id(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  size_t pos = -1;
  TodoResult res = todo_find(todos, 2, &pos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(pos == 1);
  ASSERT_TRUE(todos->data[pos].id == 2);
  ASSERT_TRUE(strcmp(todos->data[pos].title, "TEST 2") == 0);

  todo_list_destroy(&todos);
  return true;
}

bool test_find_todo_by_id_not_found(void)
{
  TodoList *todos = todo_list_create(5);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  size_t pos = -1;
  TodoResult res = todo_find(todos, 4, &pos);

  ASSERT_TRUE(res == TODO_ERR_NOT_FOUND);

  todo_list_destroy(&todos);
  return true;
}

bool test_find_todo_by_id_todos_empty(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }
  todos->size = 0; // Empty list

  size_t pos = -1;
  TodoResult res = todo_find(todos, 100, &pos);

  ASSERT_TRUE(res == TODO_ERR_EMPTY);

  todo_list_destroy(&todos);
  return true;
}

bool test_find_todo_by_id_todos_null(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }
  todos->data = NULL;

  size_t pos = -1;
  TodoResult res = todo_find(todos, 100, &pos);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_destroy(&todos);
  return true;
}

bool test_find_todo_by_id_pos_null(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  TodoResult res = todo_find(todos, 100, NULL);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_destroy(&todos);
  return true;
}

bool test_delete_todo_removes_item(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  TodoResult res = todo_delete(todos, 1);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->size == 2);
  ASSERT_TRUE(todos->data[0].id == 1);
  ASSERT_TRUE(strcmp(todos->data[0].title, "TEST 1") == 0);
  ASSERT_TRUE(todos->data[1].id == 3);
  ASSERT_TRUE(strcmp(todos->data[1].title, "TEST 3") == 0);

  todo_list_destroy(&todos);
  return true;
}

bool test_delete_todo_removes_item_out_of_bounds(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  TodoResult res = todo_delete(todos, 5);

  ASSERT_TRUE(res == TODO_ERR_OUT_OF_BOUNDS);

  todo_list_destroy(&todos);
  return true;
}

bool test_delete_todo_removes_item_todos_null(void)
{
  TodoResult res = todo_delete(NULL, 0);

  ASSERT_TRUE(res == TODO_ERR_EMPTY);

  return true;
}

bool test_toggle_todo_status_changes_value(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  TodoResult res = todo_toggle_status(todos, 1);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->data[1].done == false);

  res = todo_toggle_status(todos, 1);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->data[1].done == true);

  todo_list_destroy(&todos);
  return true;
}

bool test_toggle_todo_status_changes_value_null(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  todos->data = NULL; // Simulate null data

  TodoResult res = todo_toggle_status(todos, 1);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_toggle_todo_status_changes_todos_null(void)
{
  TodoResult res = todo_toggle_status(NULL, 0);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_toggle_todo_status_changes_out_of_bounds(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  TodoResult res = todo_toggle_status(todos, 5);

  ASSERT_TRUE(res == TODO_ERR_OUT_OF_BOUNDS);

  todo_list_destroy(&todos);

  return true;
}

bool test_change_todo_title(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  TodoResult res = todo_change_title("New Todo", todos, 1);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(strlen(todos->data[1].title) > 0);
  ASSERT_TRUE(strcmp(todos->data[1].title, "New Todo") == 0);

  todo_list_destroy(&todos);
  return true;
}

bool test_change_todo_title_todos_data_null(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  todos->data = NULL;

  TodoResult res = todo_change_title("New Todo", todos, 1);

  ASSERT_TRUE(res == TODO_ERR_EMPTY);

  todo_list_destroy(&todos);
  return true;
}

bool test_change_todo_title_todos_null(void)
{
  TodoResult res = todo_change_title("New Todo", NULL, 0);

  ASSERT_TRUE(res == TODO_ERR_EMPTY);

  return true;
}

bool test_change_todo_title_not_foudn(void)
{
  TodoList *todos = todo_list_create(10);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  _fill_stub_todos(todos, 3);

  TodoResult res = todo_change_title("NEW TEST TITLE", todos, 5);

  ASSERT_TRUE(res == TODO_ERR_NOT_FOUND);

  todo_list_destroy(&todos);
  return true;
}
