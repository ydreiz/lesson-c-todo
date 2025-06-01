#include <stdio.h>

// This program demonstrates the stack memory usage in a recursive function.
// It prints the address of the local variables `count` and `buf` at each level
// of recursion, showing how each call to the function creates a new stack
// frame.

void recursive(int count) {
  char buf[128];
  printf("Recursive level: %d, &count=%p, &buf=%p\n", count, (void *)&count,
         (void *)&buf);
  if (count > 0) {
    recursive(count - 1);
  };
}

int main(void) {
  recursive(5);
  return 0;
}
