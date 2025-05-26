#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "errors.h"
#include "test.h"

static void capture_stderr(void (*func)(const char *msg), const char *msg, char *out_buf, size_t buf_size)
{
  FILE *old_stderr = stderr;
  FILE *tmp = tmpfile();
  assert(tmp != NULL);

  stderr = tmp;
  func(msg);
  fflush(tmp);

  rewind(tmp);
  size_t n = fread(out_buf, 1, buf_size - 1, tmp);
  out_buf[n] = '\0';

  fclose(tmp);
  stderr = old_stderr;
}

bool test_error_enable_diable_logging()
{
  enable_logging(false);
  ASSERT_TRUE(!is_logging_enabled());

  enable_logging(true);
  ASSERT_TRUE(is_logging_enabled());

  return true;
}

bool test_error_print_error_enabled()
{
  enable_logging(true);

  char output[1024];

  capture_stderr(p_error, "This is an error message", output, sizeof(output));

  ASSERT_TRUE(strstr(output, "[ERROR] This is an error message") != NULL);

  return true;
}

bool test_error_print_error_disabled()
{
  enable_logging(false);

  char output[1024];

  capture_stderr(p_error, "This is an error message", output, sizeof(output));

  ASSERT_TRUE(strlen(output) == 0);

  return true;
}

bool test_error_print_warn_enabled()
{
  enable_logging(true);

  char output[1024];

  capture_stderr(p_warn, "This is a warning message", output, sizeof(output));

  ASSERT_TRUE(strstr(output, "[WARN] This is a warning message") != NULL);

  return true;
}

bool test_error_print_warn_disabled()
{
  enable_logging(false);

  char output[1024];

  capture_stderr(p_warn, "This is a warning message", output, sizeof(output));

  ASSERT_TRUE(strlen(output) == 0);

  return true;
}

bool test_error_print_info_enabled()
{
  enable_logging(true);

  char output[1024];

  capture_stderr(p_info, "This is an info message", output, sizeof(output));

  ASSERT_TRUE(strstr(output, "[INFO] This is an info message") != NULL);

  return true;
}

bool test_error_print_info_disabled()
{
  enable_logging(false);

  char output[1024];

  capture_stderr(p_info, "This is an info message", output, sizeof(output));

  ASSERT_TRUE(strlen(output) == 0);

  return true;
}
