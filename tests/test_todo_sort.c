#include <stdio.h>
#include <string.h>

#include "test.h"
#include "todo_common.h"
#include "todo_list.h"
#include "todo_sort.h"

void fill_stub_todos(TodoList *todos, size_t size);

bool test_todos_list_sort_empty(void)
{
  TodoList *todos = todo_list_create(1);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->size = 0; // Empty list

  todo_list_sort(todo_compare_id_asc, todos);

  ASSERT_TRUE(todos->size == 0); // Should remain empty

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_sort_by_id_asc(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 3);

  todo_list_sort(todo_compare_id_asc, todos);

  ASSERT_TRUE(todos->data[0].id == 1);
  ASSERT_TRUE(todos->data[1].id == 2);
  ASSERT_TRUE(todos->data[2].id == 3);
  ASSERT_TRUE(strcmp(todos->data[0].title, "TEST 1") == 0);
  ASSERT_TRUE(strcmp(todos->data[1].title, "TEST 2") == 0);
  ASSERT_TRUE(strcmp(todos->data[2].title, "TEST 3") == 0);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_sort_by_id_desc(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 3);

  todo_list_sort(todo_compare_id_desc, todos);

  ASSERT_TRUE(todos->data[0].id == 3);
  ASSERT_TRUE(todos->data[1].id == 2);
  ASSERT_TRUE(todos->data[2].id == 1);
  ASSERT_TRUE(strcmp(todos->data[0].title, "TEST 3") == 0);
  ASSERT_TRUE(strcmp(todos->data[1].title, "TEST 2") == 0);
  ASSERT_TRUE(strcmp(todos->data[2].title, "TEST 1") == 0);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_sort_by_status_asc(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 3);

  todos->data[0].done = true;  // Set first todo as done
  todos->data[1].done = false; // Set second todo as not done
  todos->data[2].done = true;  // Set third todo as done

  todo_list_sort(todo_compare_status_asc, todos);

  ASSERT_TRUE(todos->data[0].done == false);
  ASSERT_TRUE(todos->data[1].done == true);
  ASSERT_TRUE(todos->data[2].done == true);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_sort_by_status_desc(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  fill_stub_todos(todos, 3);

  todos->data[0].done = true;  // Set first todo as done
  todos->data[1].done = false; // Set second todo as not done
  todos->data[2].done = true;  // Set third todo as done

  todo_list_sort(todo_compare_status_desc, todos);

  ASSERT_TRUE(todos->data[0].done == true);
  ASSERT_TRUE(todos->data[1].done == true);
  ASSERT_TRUE(todos->data[2].done == false);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_sort_by_title_asc(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->data[0] = (Todo){.id = 1, .done = false, .title = u_strdup("Best task")};
  todos->data[1] = (Todo){.id = 2, .done = false, .title = u_strdup("Fat task")};
  todos->data[2] = (Todo){.id = 3, .done = false, .title = u_strdup("XYZ task")};

  todo_list_sort(todo_compare_title_asc, todos);

  ASSERT_TRUE(strcmp(todos->data[0].title, "Best task") == 0);
  ASSERT_TRUE(strcmp(todos->data[1].title, "Fat task") == 0);
  ASSERT_TRUE(strcmp(todos->data[2].title, "XYZ task") == 0);

  todo_list_free(&todos);
  return true;
}

bool test_todos_list_sort_by_title_desc(void)
{
  TodoList *todos = todo_list_create(3);
  ASSERT_TRUE(todos != NULL);
  ASSERT_TRUE(todos->data != NULL);

  todos->data[0] = (Todo){.id = 1, .done = false, .title = u_strdup("Best task")};
  todos->data[1] = (Todo){.id = 2, .done = false, .title = u_strdup("Fat task")};
  todos->data[2] = (Todo){.id = 3, .done = false, .title = u_strdup("XYZ task")};

  todo_list_sort(todo_compare_title_desc, todos);

  ASSERT_TRUE(strcmp(todos->data[2].title, "XYZ task") == 0);
  ASSERT_TRUE(strcmp(todos->data[1].title, "Fat task") == 0);
  ASSERT_TRUE(strcmp(todos->data[0].title, "Best task") == 0);

  todo_list_free(&todos);
  return true;
}

void run_test_todo_sort(void)
{
  printf("==== TODO SORT ====\n");
  run_test("Todos List sort empty", test_todos_list_sort_empty);

  run_test("Todos List sort by ID ascending", test_todos_list_sort_by_id_asc);
  run_test("Todos List sort by ID descending", test_todos_list_sort_by_id_desc);

  run_test("Todos List sort by status ascending", test_todos_list_sort_by_status_asc);
  run_test("Todos List sort by status descending", test_todos_list_sort_by_status_desc);

  run_test("Todos List sort by title ascending", test_todos_list_sort_by_title_asc);
  run_test("Todos List sort by title descending", test_todos_list_sort_by_title_desc);
}
