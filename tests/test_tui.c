#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "todo.h"
#include "tui.h"

void _fill_stub_todos(TodoList *todos, size_t size);

static FILE *create_tmpfile_with_content(const char *content)
{
  FILE *tmp = tmpfile();
  if (!tmp)
  {
    perror("tmpfile");
    return NULL;
  }

  if (content)
  {
    fputs(content, tmp);
    fflush(tmp);
    rewind(tmp);
  }

  return tmp;
}

static void capture_stdout(void (*func)(const TodoList *), const TodoList *todos, char *out_buf, size_t buf_size)
{
  FILE *old_stdout = stdout;
  FILE *tmp = tmpfile();
  assert(tmp != NULL);

  stdout = tmp;
  func(todos);
  fflush(tmp);

  rewind(tmp);
  size_t n = fread(out_buf, 1, buf_size - 1, tmp);
  out_buf[n] = '\0';

  fclose(tmp);
  stdout = old_stdout;
}

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

bool test_tui_input_number_eof(void)
{
  FILE *old_stdin = stdin;

  size_t buf;
  FILE *input = create_tmpfile_with_content("\n");
  ASSERT_TRUE(input != NULL);

  stdin = input;
  TuiResult res = tui_input_number(&buf, NULL);

  ASSERT_TRUE(res == TUI_ERR_INVALID_INPUT);

  fclose(input);

  stdin = old_stdin;

  return true;
}

bool test_tui_print_todos()
{
  char output[8192];

  TodoList *todos_small = todo_list_create(3);
  _fill_stub_todos(todos_small, 2);

  TodoList *todos_medium = todo_list_create(10);
  _fill_stub_todos(todos_medium, 10);

  TodoList *todos_large = todo_list_create(100);
  _fill_stub_todos(todos_large, 100);

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

  todo_list_destroy(&todos_small);
  todo_list_destroy(&todos_medium);
  todo_list_destroy(&todos_large);

  return true;
}
