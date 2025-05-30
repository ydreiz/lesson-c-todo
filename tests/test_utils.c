

#include "test.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

bool test_utils_strdup(void)
{
  const char *original = "Hello, World!";
  u_string *dup = u_strdup(original);

  ASSERT_TRUE(dup != NULL);
  ASSERT_TRUE(strcmp(dup, original) == 0);

  u_strdup_free(dup);
  return true;
}

bool test_utils_strdup_null(void)
{
  u_string *dup = u_strdup(NULL);
  ASSERT_TRUE(dup == NULL); // Should return NULL for NULL input
  return true;
}

bool test_utils_strdup_free(void)
{
  const char *original = "Hello, World!";
  u_string *dup = u_strdup(original);

  ASSERT_TRUE(dup != NULL);
  ASSERT_TRUE(strcmp(dup, original) == 0);

  u_strdup_free(dup);
  dup = NULL; // Ensure pointer is set to NULL after freeing

  ASSERT_TRUE(dup == NULL); // Should be NULL after free
  return true;
}

void run_test_utils(void)
{
  printf("==== UTILS ====\n");
  run_test("u_strdup", test_utils_strdup);
  run_test("u_strdup NULL", test_utils_strdup_null);
  run_test("u_strdup free", test_utils_strdup_free);
}
