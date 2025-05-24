#include "test.h"

void run_test(const char *name, TestFunc test)
{
  printf("Running test: %s... ", name);
  if (test())
  {
    printf("PASSED\n");
  }
  else
  {
    printf("FAILED\n");
  }
}
