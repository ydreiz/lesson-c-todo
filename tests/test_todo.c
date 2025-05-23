#include "../include/test.h"
#include "../include/todo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool test_status_str(void) {
  ASSERT_TRUE(strcmp(status_str(true), "[x]") == 0);
  ASSERT_TRUE(strcmp(status_str(false), "[ ]") == 0);
  return true;
}

bool test_add_todo_increases_count(void) {
  size_t capacity = 2;
  size_t count = 0;
  size_t global_id = 0;
  Todo *todos = malloc(capacity * sizeof(Todo));
  if (!todos)
    return false;

  const char *mock_title = "Test Todo\n";
  const char *mock_status = "n\n";

  FILE *t_file = tmpfile();
  if (!t_file) {
    free(todos);
    return false;
  }
  fputs(mock_title, t_file);
  fputs(mock_status, t_file);
  rewind(t_file);

  FILE *original_stdin = stdin;
  stdin = t_file;

  TodoResult res = add_todo(&todos, &count, &global_id, &capacity);

  stdin = original_stdin;
  fclose(t_file);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(count == 1);
  ASSERT_TRUE(global_id == 1);
  ASSERT_TRUE(strlen(todos[0].title) > 0);

  free(todos);
  return true;
}

bool test_delete_todo_removes_item(void) {
  size_t count = 1;
  Todo todos[2] = {{1, "Test", false}};

  TodoResult res = delete_todo(todos, &count, 1);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(count == 0);

  return true;
}

bool test_toggle_todo_status_changes_value(void) {
  size_t count = 1;
  Todo todos[1] = {{1, "Test", false}};

  TodoResult res = toggle_todo_status(todos, count, 1);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos[0].done == true);

  res = toggle_todo_status(todos, count, 1);
  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(todos[0].done == false);

  return true;
}

bool test_edit_todo_title_change_title(void) {
  size_t count = 2;
  Todo todos[2] = {{1, "Test", false}, {2, "Another Test", false}};

  const char *mock_new_title = "New Todo\n";

  FILE *t_file = tmpfile();
  if (!t_file) {
    return false;
  }
  fputs(mock_new_title, t_file);
  rewind(t_file);

  FILE *original_stdin = stdin;
  stdin = t_file;

  TodoResult res = edit_todo_title(todos, count, 1);

  stdin = original_stdin;
  fclose(t_file);

  ASSERT_TRUE(res == TODO_OK);
  ASSERT_TRUE(strlen(todos[0].title) > 0);
  ASSERT_TRUE(strcmp(todos[0].title, "New Todo") == 0);

  return true;
}
