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

// bool test_delete_todo_removes_item(void) {
//   size_t count = 3;
//   Todo todos[5] = {{1, "Test", false},
//                    {2, "Another Test", false},
//                    {3, "Yet Another Test", false}};
//
//   TodoResult res = todo_delete(todos, &count, 3);
//
//   ASSERT_TRUE(res == TODO_OK);
//   ASSERT_TRUE(count == 2);
//
//   return true;
// }

// bool test_toggle_todo_status_changes_value(void) {
//   size_t count = 1;
//   Todo todos[1] = {{1, "Test", false}};
//
//   TodoResult res = toggle_todo_status(todos, count, 1);
//   ASSERT_TRUE(res == TODO_OK);
//   ASSERT_TRUE(todos[0].done == true);
//
//   res = toggle_todo_status(todos, count, 1);
//   ASSERT_TRUE(res == TODO_OK);
//   ASSERT_TRUE(todos[0].done == false);
//
//   return true;
// }
//
// bool test_edit_todo_title_change_title(void) {
//   size_t count = 2;
//   Todo todos[2] = {{1, "Test", false}, {2, "Another Test", false}};
//
//   const char *mock_new_title = "New Todo\n";
//
//   FILE *t_file = tmpfile();
//   if (!t_file) {
//     return false;
//   }
//   fputs(mock_new_title, t_file);
//   rewind(t_file);
//
//   FILE *original_stdin = stdin;
//   stdin = t_file;
//
//   TodoResult res = edit_todo_title(todos, count, 1);
//
//   stdin = original_stdin;
//   fclose(t_file);
//
//   ASSERT_TRUE(res == TODO_OK);
//   ASSERT_TRUE(strlen(todos[0].title) > 0);
//   ASSERT_TRUE(strcmp(todos[0].title, "New Todo") == 0);
//
//   return true;
// }
