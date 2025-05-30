
#include "test.h"
#include "todo_common.h"
#include "todo_filter.h"
#include "todo_list.h"
#include <string.h>

void fill_stub_todos(TodoList *todos, size_t size);

bool test_todos_list_filtered_done(void)
{
  TodoList *todos = todo_list_create(100);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 100);

  TodoList *filtered_todos = todo_list_create(50);
  ASSERT_TRUE(filtered_todos != NULL);
  ASSERT_TRUE(filtered_todos->data != NULL);

  TodoResult res = todo_list_filter(todo_is_done, todos, filtered_todos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(filtered_todos->size == 50); // 50 todos should be done

  todo_list_free(&todos);
  todo_list_free(&filtered_todos);
  return true;
}

bool test_todos_list_filtered_done_empty(void)
{
  TodoList *todos = todo_list_create(1);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->size = 0; // Empty list

  TodoList *filtered_todos = todo_list_create(1);
  ASSERT_TRUE(filtered_todos != NULL);
  ASSERT_TRUE(filtered_todos->data != NULL);

  TodoResult res = todo_list_filter(todo_is_done, todos, filtered_todos);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(filtered_todos->size == 0); // No todos should be done

  todo_list_free(&todos);
  todo_list_free(&filtered_todos);
  return true;
}

bool test_todos_list_filtered_done_null(void)
{
  TodoList *todos = todo_list_create(1);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->size = 0; // Empty list

  TodoList *filtered_todos = NULL; // Null pointer

  TodoResult res = todo_list_filter(todo_is_done, todos, filtered_todos);

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_filtered_by_id(void)
{
  TodoList *todos = todo_list_create(100);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  TodoList *filtered_todos = todo_list_create(1);
  ASSERT_TRUE(filtered_todos != NULL);
  ASSERT_TRUE(filtered_todos->data != NULL);

  fill_stub_todos(todos, 100);

  todo_list_filter(todo_find_by_id, todos, filtered_todos, 31);

  ASSERT_TRUE(filtered_todos->size == 1); // Only one todo with ID 31 should be found
  ASSERT_TRUE(filtered_todos->data[0].id == 31);

  return true;
}

bool test_todos_list_filtered_by_id_empty(void)
{
  TodoList *todos = todo_list_create(1);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->size = 0; // Empty list

  TodoList *filtered_todos = todo_list_create(1);
  ASSERT_TRUE(filtered_todos != NULL);
  ASSERT_TRUE(filtered_todos->data != NULL);

  todo_list_filter(todo_find_by_id, todos, filtered_todos, 31);

  ASSERT_TRUE(filtered_todos->size == 0);        // No todos should be found
  ASSERT_TRUE(filtered_todos->data[0].id != 31); // Data should be NULL

  todo_list_free(&todos);
  todo_list_free(&filtered_todos);
  return true;
}

bool test_todos_list_find_by_id_null(void)
{
  TodoList *todos = todo_list_create(1);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->size = 0; // Empty list

  Todo *todo = todo_list_find(todo_find_by_id, todos, 31);

  ASSERT_TRUE(todo == NULL); // Should return NULL for empty list

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_find_by_id(void)
{
  TodoList *todos = todo_list_create(100);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 100);

  Todo *todo = todo_list_find(todo_find_by_id, todos, 31);

  ASSERT_TRUE(todo != NULL);
  ASSERT_TRUE(todo->id == 31); // Should find the todo with ID 31

  todo_list_free(&todos);
  return true;
}

void run_test_todo_filter(void)
{
  printf("==== TODO FILTER ====\n");
  run_test("Todos List Filtered Done", test_todos_list_filtered_done);
  run_test("Todos List Filtered Done Empty", test_todos_list_filtered_done_empty);
  run_test("Todos List Filtered Done Null", test_todos_list_filtered_done_null);

  run_test("Todos List Filtered By ID", test_todos_list_filtered_by_id);
  run_test("Todos List Filtered By ID Empty", test_todos_list_filtered_by_id_empty);

  run_test("Todos List Find By ID Null", test_todos_list_find_by_id_null);
  run_test("Todos List Find By ID", test_todos_list_find_by_id);
}
