#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "todo_list.h"
#include "tui.h"

void fill_stub_todos(TodoList *todos, size_t size);
void capture_stdout(void (*func)(const TodoList *), const TodoList *todos, char *out_buf, size_t buf_size);
FILE *create_tmpfile_with_content(const char *content);

bool test_tui_input_text_successfuly(void)
{
  FILE *old_stdin = stdin;

  char buf[20];
  FILE *input = create_tmpfile_with_content("hello\n");
  ASSERT_TRUE(input != NULL);

  stdin = input;
  TuiResult res = tui_input_text(buf, sizeof(buf), NULL);

  ASSERT_TRUE(res == TUI_OK);
  ASSERT_TRUE(strcmp(buf, "hello") == 0);

  fclose(input);

  stdin = old_stdin;

  return true;
}

bool test_tui_input_text_empty(void)
{
  FILE *old_stdin = stdin;

  char buf[20];
  FILE *input = create_tmpfile_with_content("\n");
  ASSERT_TRUE(input != NULL);

  stdin = input;
  TuiResult res = tui_input_text(buf, sizeof(buf), NULL);

  ASSERT_TRUE(res == TUI_ERR_EMPTY_INPUT);
  ASSERT_TRUE(strlen(buf) == 0);

  fclose(input);

  stdin = old_stdin;

  return true;
}

bool test_tui_input_text_eof(void)
{
  FILE *old_stdin = stdin;

  char buf[20];
  FILE *input = create_tmpfile_with_content(NULL);
  ASSERT_TRUE(input != NULL);

  stdin = input;
  TuiResult res = tui_input_text(buf, sizeof(buf), NULL);

  ASSERT_TRUE(res == TUI_ERR_INVALID_INPUT);

  fclose(input);

  stdin = old_stdin;

  return true;
}

bool test_tui_input_number_successfuly(void)
{
  FILE *old_stdin = stdin;

  size_t buf;
  FILE *input = create_tmpfile_with_content("32\n");
  ASSERT_TRUE(input != NULL);

  stdin = input;
  TuiResult res = tui_input_number(&buf, NULL);

  ASSERT_TRUE(res == TUI_OK);
  ASSERT_TRUE(buf == 32);

  fclose(input);

  stdin = old_stdin;

  return true;
}

bool test_tui_input_number_invalid(void)
{
  FILE *old_stdin = stdin;

  size_t buf;
  FILE *input = create_tmpfile_with_content("invalid\n");
  ASSERT_TRUE(input != NULL);

  stdin = input;
  TuiResult res = tui_input_number(&buf, NULL);

  ASSERT_TRUE(res == TUI_ERR_INVALID_INPUT);

  fclose(input);

  stdin = old_stdin;

  return true;
}

bool test_tui_input_number_empty(void)
{
  FILE *old_stdin = stdin;

  size_t buf;
  FILE *input = create_tmpfile_with_content("\n");
  ASSERT_TRUE(input != NULL);

  stdin = input;
  TuiResult res = tui_input_number(&buf, NULL);

  ASSERT_TRUE(res == TUI_ERR_EMPTY_INPUT);

  fclose(input);

  stdin = old_stdin;

  return true;
}

bool test_tui_print_todos()
{
  char output[8192];

  TodoList *todos_small = todo_list_create(3);
  fill_stub_todos(todos_small, 2);

  TodoList *todos_medium = todo_list_create(10);
  fill_stub_todos(todos_medium, 10);

  TodoList *todos_large = todo_list_create(100);
  fill_stub_todos(todos_large, 100);

  // Test 1: NULL and 0 count (nothing should be output)
  capture_stdout(tui_print_todos, NULL, output, sizeof(output));
  ASSERT_TRUE(strlen(output) == 0);

  // Test 2: count < 10 (the first printf with formatting is used)
  capture_stdout(tui_print_todos, todos_small, output, sizeof(output));
  // Let's check that the output contains lines with “[1]”, “[2]” and statuses
  ASSERT_TRUE(strstr(output, "[1]") != NULL);
  ASSERT_TRUE(strstr(output, "TEST 1") != NULL);
  ASSERT_TRUE(strstr(output, "[ ]") != NULL);
  ASSERT_TRUE(strstr(output, "[x]") != NULL);
  ASSERT_TRUE(strstr(output, "Total todos: 2") != NULL);

  // Test 3: 10 <= count < 100 (second printf is used)
  capture_stdout(tui_print_todos, todos_medium, output, sizeof(output));
  // Check for the presence of “[ 1]” (with two spaces), “[10]”
  ASSERT_TRUE(strstr(output, "[ 1]") != NULL);
  ASSERT_TRUE(strstr(output, "[10]") != NULL);
  ASSERT_TRUE(strstr(output, "Total todos: 10") != NULL);

  // Test 4: count >= 100 (third printf is used)
  capture_stdout(tui_print_todos, todos_large, output, sizeof(output));
  // Let's check for the presence of “[ 1]” (with three spaces), “[100]”
  ASSERT_TRUE(strstr(output, "[  1]") != NULL);
  ASSERT_TRUE(strstr(output, "[100]") != NULL);
  ASSERT_TRUE(strstr(output, "Total todos: 100") != NULL);

  todo_list_free(&todos_small);
  todo_list_free(&todos_medium);
  todo_list_free(&todos_large);

  return true;
}

void run_test_tui(void)
{
  printf("==== TUI ====\n");

  run_test("Input text successfuly", test_tui_input_text_successfuly);
  run_test("Input text empty", test_tui_input_text_empty);
  run_test("Input text EOF", test_tui_input_text_eof);
  run_test("Input number successfuly", test_tui_input_number_successfuly);
  run_test("Input number invalid", test_tui_input_number_invalid);
  run_test("Input number empty", test_tui_input_number_empty);
  run_test("Print todos", test_tui_print_todos);
}
