#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "errors.h"
#include "test.h"

void capture_stderr(void (*func)(const char *msg), const char *msg, char *out_buf, size_t buf_size);

bool test_error_enable_diable_logging()
{
  enable_logging(false);
  ASSERT_TRUE(!is_logging_enabled());

  enable_logging(true);
  ASSERT_TRUE(is_logging_enabled());

  return true;
}

bool test_error_print_error()
{
  char output[1024];

  enable_logging(true);
  capture_stderr(p_error, "This is an error message", output, sizeof(output));
  ASSERT_TRUE(strstr(output, "[ERROR] This is an error message") != NULL);

  enable_logging(false);
  capture_stderr(p_error, "This is an error message", output, sizeof(output));
  ASSERT_TRUE(strlen(output) == 0);

  return true;
}

bool test_error_print_warn()
{
  char output[1024];

  enable_logging(true);
  capture_stderr(p_warn, "This is a warning message", output, sizeof(output));
  ASSERT_TRUE(strstr(output, "[WARN] This is a warning message") != NULL);

  enable_logging(false);
  capture_stderr(p_warn, "This is a warning message", output, sizeof(output));
  ASSERT_TRUE(strlen(output) == 0);

  return true;
}

bool test_error_print_info()
{
  char output[1024];

  enable_logging(true);
  capture_stderr(p_info, "This is an info message", output, sizeof(output));
  ASSERT_TRUE(strstr(output, "[INFO] This is an info message") != NULL);

  enable_logging(false);
  capture_stderr(p_info, "This is an info message", output, sizeof(output));
  ASSERT_TRUE(strlen(output) == 0);

  return true;
}

void run_test_errors(void)
{
  printf("==== ERRORS ====\n");
  run_test("toggle logging", test_error_enable_diable_logging);
  run_test("print error enabled", test_error_print_error);
  run_test("print warn enabled", test_error_print_warn);
  run_test("print info enabled", test_error_print_info);
}
