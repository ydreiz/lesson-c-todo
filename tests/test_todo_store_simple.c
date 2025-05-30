#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "todo_list.h"
#include "todo_store_simple.h"
#include "utils.h"

#define TEST_FILE "test_todos.txt"

bool test_save_and_load_todos(void)
{
  TodoList *todos_save = todo_list_create(2);
  ASSERT_TRUE(todos_save != NULL);
  ASSERT_TRUE(todos_save->data != NULL);

  todos_save->data[0] = (Todo){.id = 1, .done = false, .title = u_strdup("Task One")};
  todos_save->data[1] = (Todo){.id = 2, .done = true, .title = u_strdup("Task Two")};

  TodoResult save_res = todo_save(TEST_FILE, todos_save);
  ASSERT_TRUE(save_res == TODO_OK);

  TodoList *todos_load = todo_list_create(2);
  ASSERT_TRUE(todos_load != NULL);
  ASSERT_TRUE(todos_load->data != NULL);

  TodoResult load_res = todo_load(TEST_FILE, todos_load);
  ASSERT_TRUE(load_res == TODO_OK);
  ASSERT_TRUE(todos_load->size == todos_save->size);

  for (size_t i = 0; i < todos_load->size; i++)
  {
    ASSERT_TRUE(todos_save->data[i].id == todos_save->data[i].id);
    ASSERT_TRUE(strcmp(todos_save->data[i].title, todos_save->data[i].title) == 0);
    ASSERT_TRUE(todos_save->data[i].done == todos_save->data[i].done);
  }

  remove(TEST_FILE);

  todo_list_free(&todos_save);
  todo_list_free(&todos_load);

  return true;
}

bool test_load_nonexistent_file(void)
{
  TodoList *todos = todo_list_create(2);
  if (!todos || !todos->data)
  {
    todo_list_free(&todos);
    return false;
  }

  TodoResult res = todo_load("nonexistent_file.txt", todos);
  ASSERT_TRUE(res == TODO_ERR_FILE);

  todo_list_free(&todos);

  return true;
}

void run_test_todo_store_simple(void)
{
  printf("==== TODO STORE SIMPLE ====\n");

  run_test("Save and Load Todos", test_save_and_load_todos);
  run_test("Load Nonexistent File", test_load_nonexistent_file);
}
