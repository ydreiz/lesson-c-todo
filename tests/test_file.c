#include "../include/test.h"
#include "../include/todo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE "test_todos.txt"

bool test_save_and_load_todos(void) {
  size_t capacity = 2;
  size_t count = 2;
  size_t global_id = 2;

  Todo *todos = malloc(capacity * sizeof(Todo));
  if (!todos)
    return false;

  todos[0].id = 1;
  strcpy(todos[0].title, "Task One");
  todos[0].done = false;

  todos[1].id = 2;
  strcpy(todos[1].title, "Task Two");
  todos[1].done = true;

  TodoResult save_res = save_todos(TEST_FILE, todos, &count);
  ASSERT_TRUE(save_res == TODO_OK);

  size_t load_capacity = 1;
  size_t load_count = 0;
  Todo *loaded_todos = malloc(load_capacity * sizeof(Todo));
  if (!loaded_todos) {
    free(todos);
    return false;
  }

  TodoResult load_res =
      load_todos(TEST_FILE, &loaded_todos, &load_capacity, &load_count);
  ASSERT_TRUE(load_res == TODO_OK);
  ASSERT_TRUE(load_count == count);

  for (size_t i = 0; i < load_count; i++) {
    ASSERT_TRUE(loaded_todos[i].id == todos[i].id);
    ASSERT_TRUE(strcmp(loaded_todos[i].title, todos[i].title) == 0);
    ASSERT_TRUE(loaded_todos[i].done == todos[i].done);
  }

  free(todos);
  free(loaded_todos);

  remove(TEST_FILE);

  return true;
}

bool test_load_nonexistent_file(void) {
  size_t capacity = 2;
  size_t count = 0;
  Todo *todos = malloc(capacity * sizeof(Todo));
  if (!todos)
    return false;

  TodoResult res =
      load_todos("nonexistent_file.txt", &todos, &capacity, &count);
  ASSERT_TRUE(res == TODO_ERR_FILE);

  free(todos);
  return true;
}
