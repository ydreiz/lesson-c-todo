#include "test.h"

void run_test(const char *name, TestFunc test)
{
  if (test())
  {
    printf("\033[0;32mPASSED\033[0m");
  }
  else
  {
    printf("\033[0;31mFAILED\033[0m");
  }
  printf(": %s\n", name);
}
