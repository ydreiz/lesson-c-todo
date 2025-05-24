#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../include/test.h"
#include "../include/tui.h"

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

static void capture_stdout(void (*func)(const Todo[], size_t), const Todo *todos, size_t count, char *out_buf,
                           size_t buf_size)
{
  FILE *old_stdout = stdout;
  FILE *tmp = tmpfile();
  assert(tmp != NULL);

  stdout = tmp;
  func(todos, count);
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
  Todo todos_small[] = {{1, "Task one", false}, {2, "Task two", true}};

  Todo todos_medium[10];
  for (size_t i = 0; i < 10; i++)
  {
    todos_medium[i].id = i + 1;
    snprintf(todos_medium[i].title, sizeof(todos_medium[i].title), "Task %zu", i + 1);
    todos_medium[i].done = (i % 2 == 0);
  }

  Todo todos_large[100];
  for (size_t i = 0; i < 100; i++)
  {
    todos_large[i].id = i + 1;
    snprintf(todos_large[i].title, sizeof(todos_large[i].title), "Task %zu", i + 1);
    todos_large[i].done = (i % 3 == 0);
  }

  // Test 1: NULL and 0 count (nothing should be output)
  capture_stdout(tui_print_todos, NULL, 0, output, sizeof(output));
  ASSERT_TRUE(strlen(output) == 0);

  // Test 2: count < 10 (the first printf with formatting is used)
  capture_stdout(tui_print_todos, todos_small, 2, output, sizeof(output));
  // Let's check that the output contains lines with “[1]”, “[2]” and statuses
  ASSERT_TRUE(strstr(output, "[1]") != NULL);
  ASSERT_TRUE(strstr(output, "Task one") != NULL);
  ASSERT_TRUE(strstr(output, "[ ]") != NULL);
  ASSERT_TRUE(strstr(output, "[x]") != NULL);
  ASSERT_TRUE(strstr(output, "Total todos: 2") != NULL);

  // Test 3: 10 <= count < 100 (second printf is used)
  capture_stdout(tui_print_todos, todos_medium, 10, output, sizeof(output));
  // Check for the presence of “[ 1]” (with two spaces), “[10]”
  ASSERT_TRUE(strstr(output, "[ 1]") != NULL);
  ASSERT_TRUE(strstr(output, "[10]") != NULL);
  ASSERT_TRUE(strstr(output, "Total todos: 10") != NULL);

  // Test 4: count >= 100 (third printf is used)
  capture_stdout(tui_print_todos, todos_large, 100, output, sizeof(output));
  // Let's check for the presence of “[ 1]” (with three spaces), “[100]”
  ASSERT_TRUE(strstr(output, "[  1]") != NULL);
  ASSERT_TRUE(strstr(output, "[100]") != NULL);
  ASSERT_TRUE(strstr(output, "Total todos: 100") != NULL);

  return true;
}
