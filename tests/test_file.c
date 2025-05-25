#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "todo.h"

#define TEST_FILE "test_todos.txt"

bool test_save_and_load_todos(void)
{
  TodoList *todos_save = todo_list_create(2);
  if (!todos_save || !todos_save->data)
  {
    todo_list_destroy(&todos_save);
    return false;
  }

  todos_save->data[0].id = 1;
  strcpy(todos_save->data[0].title, "Task One");
  todos_save->data[0].done = false;

  todos_save->data[1].id = 2;
  strcpy(todos_save->data[1].title, "Task Two");
  todos_save->data[1].done = true;

  TodoResult save_res = todo_save(TEST_FILE, todos_save);
  ASSERT_TRUE(save_res == TODO_OK);

  TodoList *todos_load = todo_list_create(2);
  if (!todos_load || !todos_load->data)
  {
    todo_list_destroy(&todos_load);
    return false;
  }

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

  todo_list_destroy(&todos_save);
  todo_list_destroy(&todos_load);

  return true;
}

bool test_load_nonexistent_file(void)
{
  TodoList *todos = todo_list_create(2);
  if (!todos || !todos->data)
  {
    todo_list_destroy(&todos);
    return false;
  }

  TodoResult res = todo_load("nonexistent_file.txt", todos);
  ASSERT_TRUE(res == TODO_ERR_FILE);

  todo_list_destroy(&todos);

  return true;
}
