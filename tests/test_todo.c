#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "todo.h"
#include "todo_list.h"

void fill_stub_todos(TodoList *todos, size_t size);

bool test_add_todo(void)
{
  TodoList *todos = todo_list_create(2);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  TodoResult res = todo_add("TEST TODO NAME", true, todos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->size == 1);
  ASSERT_TRUE(todos->next_id == 2);

  ASSERT_TRUE(strlen(todos->data[0].title) > 0);
  ASSERT_TRUE(strcmp(todos->data[0].title, "TEST TODO NAME") == 0);
  ASSERT_TRUE(todos->data[0].done == true);

  todo_list_free(&todos);
  return true;
}

bool test_find_todo_by_id(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  size_t pos = -1;
  TodoResult res = todo_find_idx(todos, 2, &pos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(pos == 1);
  ASSERT_TRUE(todos->data[pos].id == 2);
  ASSERT_TRUE(strcmp(todos->data[pos].title, "TEST 2") == 0);

  todo_list_free(&todos);
  return true;
}

bool test_find_todo_by_id_not_found(void)
{
  TodoList *todos = todo_list_create(5);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  size_t pos = -1;
  TodoResult res = todo_find_idx(todos, 4, &pos);

  ASSERT_TRUE(res == TODO_ERR_NOT_FOUND);

  todo_list_free(&todos);
  return true;
}

bool test_find_todo_by_id_todos_empty(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }
  todos->size = 0; // Empty list

  size_t pos = -1;
  TodoResult res = todo_find_idx(todos, 100, &pos);

  ASSERT_TRUE(res == TODO_ERR_EMPTY);

  todo_list_free(&todos);
  return true;
}

bool test_find_todo_by_id_todos_null(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }
  todos->data = NULL;

  size_t pos = -1;
  TodoResult res = todo_find_idx(todos, 100, &pos);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_free(&todos);
  return true;
}

bool test_find_todo_by_id_pos_null(void)
{
  TodoList *todos = todo_list_create(1);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  TodoResult res = todo_find_idx(todos, 100, NULL);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_free(&todos);
  return true;
}

bool test_delete_todo_removes_item(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  TodoResult res = todo_delete(todos, 1);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->size == 2);
  ASSERT_TRUE(todos->data[0].id == 1);
  ASSERT_TRUE(strcmp(todos->data[0].title, "TEST 1") == 0);
  ASSERT_TRUE(todos->data[1].id == 3);
  ASSERT_TRUE(strcmp(todos->data[1].title, "TEST 3") == 0);

  todo_list_free(&todos);
  return true;
}

bool test_delete_todo_removes_item_out_of_bounds(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  TodoResult res = todo_delete(todos, 5);

  ASSERT_TRUE(res == TODO_ERR_OUT_OF_BOUNDS);

  todo_list_free(&todos);
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
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  TodoResult res = todo_toggle_status(todos, 1);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->data[1].done == false);

  res = todo_toggle_status(todos, 1);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->data[1].done == true);

  todo_list_free(&todos);
  return true;
}

bool test_toggle_todo_status_changes_value_null(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
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
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  TodoResult res = todo_toggle_status(todos, 5);

  ASSERT_TRUE(res == TODO_ERR_OUT_OF_BOUNDS);

  todo_list_free(&todos);

  return true;
}

bool test_change_todo_title(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  TodoResult res = todo_change_title("New Todo", todos, 1);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(strlen(todos->data[1].title) > 0);
  ASSERT_TRUE(strcmp(todos->data[1].title, "New Todo") == 0);

  todo_list_free(&todos);
  return true;
}

bool test_change_todo_title_todos_data_null(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  todos->data = NULL;

  TodoResult res = todo_change_title("New Todo", todos, 1);

  ASSERT_TRUE(res == TODO_ERR_EMPTY);

  todo_list_free(&todos);
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
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  TodoResult res = todo_change_title("NEW TEST TITLE", todos, 5);

  ASSERT_TRUE(res == TODO_ERR_NOT_FOUND);

  todo_list_free(&todos);
  return true;
}

bool test_todo_deep_clone(void)
{
  TodoList *todos = todo_list_create(3);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  fill_stub_todos(todos, 3);

  Todo clone;
  TodoResult res = todo_deep_clone(&clone, todos->data[1]);

  ASSERT_TRUE(&clone != &todos->data[1]); // Ensure clone is a different object
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(clone.id == todos->data[1].id);
  ASSERT_TRUE(strcmp(clone.title, todos->data[1].title) == 0);
  ASSERT_TRUE(clone.done == todos->data[1].done);

  u_strdup_free(clone.title);
  todo_list_free(&todos);
  return true;
}

void run_test_todo(void)
{
  printf("==== TODO ====\n");
  run_test("Add Todo success", test_add_todo);

  run_test("Find Todo by ID", test_find_todo_by_id);
  run_test("Find Todo by ID not found", test_find_todo_by_id_not_found);
  run_test("Find Todo by ID when todos are empty", test_find_todo_by_id_todos_empty);
  run_test("Find Todo by ID when todos is NULL", test_find_todo_by_id_todos_null);
  run_test("Find Todo by ID when pos is NULL", test_find_todo_by_id_pos_null);

  run_test("Delete Todo removes item", test_delete_todo_removes_item);
  run_test("Delete Todo removes item out of bounds", test_delete_todo_removes_item_out_of_bounds);
  run_test("Delete Todo removes item when todos is NULL", test_delete_todo_removes_item_todos_null);

  run_test("Toggle Todo status changes value", test_toggle_todo_status_changes_value);
  run_test("Toggle Todo status changes todos is NULL", test_toggle_todo_status_changes_todos_null);
  run_test("Toggle Todo status changes value is NULL", test_toggle_todo_status_changes_value_null);
  run_test("Toggle Todo status changes out of bounds", test_toggle_todo_status_changes_out_of_bounds);

  run_test("Change Todo title", test_change_todo_title);
  run_test("Change Todo title when todos is NULL", test_change_todo_title_todos_null);
  run_test("Change Todo title when todos is empty", test_change_todo_title_not_foudn);
  run_test("Change Todo title when todos data is NULL", test_change_todo_title_todos_data_null);

  run_test("Todo deep clone", test_todo_deep_clone);
}
