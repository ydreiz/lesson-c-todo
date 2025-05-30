#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdio.h>

#define ASSERT_TRUE(cond)                                                                                              \
  do                                                                                                                   \
  {                                                                                                                    \
    if (!(cond))                                                                                                       \
    {                                                                                                                  \
      printf("Assertion failed: %s, function %s, line %d\n", #cond, __func__, __LINE__);                               \
      return false;                                                                                                    \
    }                                                                                                                  \
  } while (0)

typedef bool (*TestFunc)(void);

void run_test(const char *name, TestFunc test);

#endif // TEST_H
