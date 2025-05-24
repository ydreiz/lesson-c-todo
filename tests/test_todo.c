#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/test.h"
#include "../include/todo.h"

bool test_add_todo_increases_count(void)
{
  size_t capacity = 2;
  size_t count = 0;
  size_t global_id = 0;
  Todo *todos = malloc(capacity * sizeof(Todo));
  if (!todos)
    return false;

  TodoResult res = todo_add("TEST TODO NAME", true, &todos, &count, &global_id, &capacity);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(count == 1);
  ASSERT_TRUE(global_id == 1);

  ASSERT_TRUE(strlen(todos[0].title) > 0);
  ASSERT_TRUE(strcmp(todos[0].title, "TEST TODO NAME") == 0);
  ASSERT_TRUE(todos[0].done == true);

  free(todos);
  return true;
}

bool test_add_todo_failure_realloc(void)
{
  size_t capacity = 0; // Set capacity to 0 to force realloc failure
  size_t count = 10;
  size_t global_id = 0;
  Todo *todos = malloc(1 * sizeof(Todo)); // Allocate a small initial size
  if (!todos)
    return false;

  TodoResult res = todo_add("TEST TODO NAME", true, &todos, &count, &global_id, &capacity);

  ASSERT_TRUE(res == TODO_ERR_ALLOC);

  return true;
}

bool test_find_todo_by_id(void)
{
  size_t count = 3;
  Todo todos[5] = {{1, "Test", false}, {2, "Another Test", false}, {3, "Yet Another Test", false}};

  size_t pos = -1;
  TodoResult res = todo_find(todos, count, 2, &pos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(pos == 1);
  ASSERT_TRUE(todos[pos].id == 2);
  ASSERT_TRUE(strcmp(todos[pos].title, "Another Test") == 0);

  return true;
}

bool test_find_todo_by_id_not_found(void)
{
  size_t count = 3;
  Todo todos[5] = {{1, "Test", false}, {2, "Another Test", false}, {3, "Yet Another Test", false}};

  size_t pos = -1;
  TodoResult res = todo_find(todos, count, 4, &pos);

  ASSERT_TRUE(res == TODO_ERR_NOT_FOUND);

  return true;
}

bool test_find_todo_by_id_todos_empty(void)
{
  size_t count = 0;
  Todo todos[2] = {};

  size_t pos = -1;
  TodoResult res = todo_find(todos, count, 100, &pos);

  ASSERT_TRUE(res == TODO_ERR_EMPTY);

  return true;
}

bool test_find_todo_by_id_todos_null(void)
{
  size_t count = 0;
  Todo *todos = NULL;

  size_t pos = -1;
  TodoResult res = todo_find(todos, count, 100, &pos);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_find_todo_by_id_pos_null(void)
{
  size_t count = 0;
  Todo *todos = {};

  TodoResult res = todo_find(todos, count, 100, NULL);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_delete_todo_removes_item(void)
{
  size_t count = 3;
  Todo todos[5] = {{1, "Test", false}, {2, "Another Test", false}, {3, "Yet Another Test", false}};
  size_t remove_pos = 1; // Remove the second item (id 2)

  TodoResult res = todo_delete(todos, &count, remove_pos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(count == 2);
  ASSERT_TRUE(todos[0].id == 1);
  ASSERT_TRUE(strcmp(todos[0].title, "Test") == 0);
  ASSERT_TRUE(todos[1].id == 3);
  ASSERT_TRUE(strcmp(todos[1].title, "Yet Another Test") == 0);

  return true;
}

bool test_delete_todo_removes_item_out_of_bounds(void)
{
  size_t count = 4;
  Todo todos[5] = {{1, "Test", false}, {2, "Another Test", false}, {3, "Yet Another Test", false}};
  size_t remove_pos = 5; // Attempt to remove an item at an out-of-bounds index

  TodoResult res = todo_delete(todos, &count, remove_pos);

  ASSERT_TRUE(res == TODO_ERR_OUT_OF_BOUNDS);

  return true;
}

bool test_delete_todo_removes_item_todos_null(void)
{
  size_t count = 0;
  TodoResult res = todo_delete(NULL, &count, 0);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_delete_todo_removes_item_count_null(void)
{
  Todo todos[1] = {{1, "Test", false}};
  TodoResult res = todo_delete(NULL, NULL, 0);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_toggle_todo_status_changes_value(void)
{
  Todo todos[1] = {{1, "Test", false}};
  size_t pos = 0;

  TodoResult res = todo_toggle_status(todos, pos);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos[0].done == true);

  res = todo_toggle_status(todos, pos);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos[0].done == false);

  return true;
}

bool test_toggle_todo_status_changes_value_todos_null(void)
{
  TodoResult res = todo_toggle_status(NULL, 0);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_change_todo_title(void)
{
  size_t count = 3;
  Todo todos[3] = {{1, "Test", false}, {2, "Another Test", false}, {3, "Yet Another Test", false}};

  TodoResult res = todo_change_title("New Todo", todos, 1);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(strlen(todos[1].title) > 0);
  ASSERT_TRUE(strcmp(todos[1].title, "New Todo") == 0);

  return true;
}

bool test_change_todo_title_todos_null(void)
{
  TodoResult res = todo_change_title("New Todo", NULL, 0);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}

bool test_change_todo_title_null(void)
{
  Todo todos[1] = {{1, "Test", false}};

  TodoResult res = todo_change_title(NULL, todos, 0);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  return true;
}
