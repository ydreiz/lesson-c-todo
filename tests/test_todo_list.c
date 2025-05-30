#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "todo_list.h"
#include "utils.h"

void fill_stub_todos(TodoList *todos, size_t size);

bool test_todos_list_create(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);
  ASSERT_TRUE(todos->size == 0);
  ASSERT_TRUE(todos->next_id == 1);
  ASSERT_TRUE(todos->capacity == 3);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_create_capacity_zero(void)
{
  TodoList *todos = todo_list_create(0);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->size == 0);
  ASSERT_TRUE(todos->next_id == 1);
  ASSERT_TRUE(todos->capacity == INITIAL_CAPACITY);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_create_capacity_overflow(void)
{
  TodoList *todos = todo_list_create(SIZE_MAX);
  ASSERT_TRUE(todos == NULL);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_resize_capacity_zero(void)
{
  TodoList *todos = todo_list_create(0);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->capacity = 0; // Simulate zero capacity

  TodoResult res = todo_list_resize(todos);

  ASSERT_TRUE(res == TODO_ERR_ALLOC);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_resize_invalid_argument(void)
{
  TodoResult res = todo_list_resize(NULL);
  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  TodoList *todos = todo_list_create(1);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  free(todos->data); // Simulate invalid argument
  todos->data = NULL;

  res = todo_list_resize(todos);
  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_free(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todo_list_free(&todos);
  ASSERT_TRUE(todos == NULL);

  return true;
}

bool test_todos_list_reacalculate_next_id(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->data[0] = (Todo){.id = 1000, .done = false, .title = u_strdup("Todo 1")};
  todos->data[1] = (Todo){.id = 2333, .done = true, .title = u_strdup("Todo 2")};
  todos->size = 2;    // Simulate two todos
  todos->next_id = 5; // Set next_id to a non-default value

  todo_list_recalculate_next_id(todos);
  ASSERT_TRUE(todos->next_id == 2334); // Next ID should be the todo ID + 1

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_reacalculate_next_id_skeep(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todo_list_recalculate_next_id(todos);

  ASSERT_TRUE(todos->next_id == 1); // Should reset to default next_id

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_add(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  Todo todo = {.id = 0, .done = false, .title = u_strdup("Test Todo")};
  TodoResult res = todo_list_add(todos, todo);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->size == 1);
  ASSERT_TRUE(todos->data[0].id == 1);
  ASSERT_TRUE(strcmp(todos->data[0].title, "Test Todo") == 0);

  ASSERT_TRUE(todos->next_id == 2); // Next ID should be incremented

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_add_capacity_increase(void)
{
  TodoList *todos = todo_list_create(2);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  // Fill the list to capacity
  for (size_t i = 0; i < 2; i++)
  {
    Todo todo = {.id = 0, .done = false, .title = u_strdup("Test Todo")};
    todo_list_add(todos, todo);
  }

  // Add another item to trigger resize
  Todo todo = {.id = 0, .done = false, .title = u_strdup("New Test Todo")};
  TodoResult res = todo_list_add(todos, todo);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->size == 3);    // Size should increase
  ASSERT_TRUE(todos->capacity > 2); // Capacity should have increased

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_add_failure_allocat_memory(void)
{
  TodoList *todos = todo_list_create(0);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  // Simulate a failure by setting capacity to zero
  todos->capacity = 0;

  Todo todo = {.id = 0, .done = false, .title = u_strdup("Test Todo")};
  TodoResult res = todo_list_add(todos, todo);

  ASSERT_TRUE(res == TODO_ERR_ALLOC); // Should fail due to zero capacity

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_add_invalid_argument(void)
{
  TodoResult res = todo_list_add(NULL, (Todo){0});

  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT); // Should fail due to null data

  return true;
}

bool test_todos_list_delete_invalida_argement(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->data = NULL; // Simulate null data

  TodoResult res = todo_list_delete(todos, 1);
  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT); // Should fail due to null data

  res = todo_list_delete(NULL, 1); // Should also fail due to null todos
  ASSERT_TRUE(res == TODO_ERR_INVALID_ARGUMENT);

  todo_list_free(&todos);

  return true;
}

bool test_todos_list_delete_array_empty(void)
{
  TodoList *todos = todo_list_create(1);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  TodoResult res = todo_list_delete(todos, 10);
  ASSERT_TRUE(res == TODO_ERR_EMPTY); // Should fail due to empty list

  todo_list_free(&todos);
  return true;
}

bool tets_todos_list_delete_not_found(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 3);

  TodoResult res = todo_list_delete(todos, 5); // ID not found
  ASSERT_TRUE(res == TODO_ERR_NOT_FOUND);      // Should fail due to not found

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_delete(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 3);

  TodoResult res = todo_list_delete(todos, 1); // Delete first todo
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos->size == 2);       // Size should decrease
  ASSERT_TRUE(todos->data[0].id == 2); // ID of the new first todo

  todo_list_free(&todos);
  return true;
}

void run_test_todo_list(void)
{
  printf("==== TODO LIST ====\n");
  run_test("Todos List Create", test_todos_list_create);
  run_test("Todos List Create Capacity Zero", test_todos_list_create_capacity_zero);
  run_test("Todos List Create Capacity Overflow", test_todos_list_create_capacity_overflow);

  run_test("Todos List Resize Capacity Zero", test_todos_list_resize_capacity_zero);
  run_test("Todos List Resize Invalid Argument", test_todos_list_resize_invalid_argument);

  run_test("Todos List Free", test_todos_list_free);

  run_test("Todos List Recalculate Next ID", test_todos_list_reacalculate_next_id);
  run_test("Todos List Recalculate Next ID Skip", test_todos_list_reacalculate_next_id_skeep);

  run_test("Todos List Add Success", test_todos_list_add);
  run_test("Todos List Add Capacity Increase", test_todos_list_add_capacity_increase);
  run_test("Todos List Add Failure", test_todos_list_add_failure_allocat_memory);
  run_test("Todos List Add Invalid Argument", test_todos_list_add_invalid_argument);

  run_test("Todos List Delete Invalid Argument", test_todos_list_delete_invalida_argement);
  run_test("Todos List Delete Array Empty", test_todos_list_delete_array_empty);
  run_test("Todos List Delete Not Found", tets_todos_list_delete_not_found);
  run_test("Todos List Delete", test_todos_list_delete);
}
