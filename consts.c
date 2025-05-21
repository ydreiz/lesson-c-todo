#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f1(const int *p) {
  printf("void f1(const int *p)\n");
  printf("\tp: %p\n", p);     // This will print the address of a1
  printf("\t*p: %d\n\n", *p); // This will print 10
  // *p = 42;  // This line will cause a compilation error
  printf("\t*p = 42; // This line will cause a compilation error\n");
  p = NULL; // This line is valid, but it does not affect the original pointer
            // passed to the function
  printf("\tp = NULL;\n");
  printf("\tp: %p\n", p); // This will print NULL
  // printf("*p: %d\n", *p); // This will cause a runtime error
  printf(
      "\tprintf(\"*p: %%d\\n\", *p); // This will cause a runtime error\n\n");
}

void f2(int *const p) {
  printf("void f2(int *const p)\n");
  printf("\tp: %p\n", p);     // This will print the address of a2
  printf("\t*p: %d\n\n", *p); // This will print 10
  *p = 42; // This line is valid, it modifies the value pointed to by p
  printf("\t*p = 42;\n");
  // p = NULL; // Cannot modify the original pointer passed to the function
  printf("\tp = NULL; // Cannot modify the original pointer passed to the "
         "function\n");
}

void f3(const int *const p) {
  printf("void f3(const int *const p)\n");
  printf("\tp: %p\n", p);     // This will print the address of a3
  printf("\t*p: %d\n\n", *p); // This will print 10
  // *p = 42;  // This line will cause a compilation error
  printf("\t*p = 42; // This line will cause a compilation error\n");
  printf("\tp = NULL; // Cannot modify the original pointer passed to the "
         "function\n");
}

void f4(int *p) {
  printf("void f4(int *p)\n");
  printf("\tp: %p\n", p);     // This will print the address of a1
  printf("\t*p: %d\n\n", *p); // This will print 10
  *p = 42;
  printf("\t*p = 42;\n");

  p = NULL;
  printf("\tp = NULL;\n\n");

  printf("\tp: %p\n", p);
  // printf("*p: %d\n", *p); // This will cause a runtime error
  printf(
      "\tprintf(\"*p: %%d\\n\", *p); // This will cause a runtime error\n\n");
}

void print_message(const char *const msg) {
  // strcpy(msg, "H"); // This line will cause a compilation error
  printf("%s\n", msg);
}

int main(void) {

  int a1 = 10;
  printf("int a1 = %d;\n", a1);
  f1(&a1);
  printf("f1(&a1);\n");
  printf("a1: %d\n\n", a1); // a1 remains 10

  int a2 = 10;
  printf("int a2 = %d;\n", a2);
  f2(&a2);
  printf("f2(&a2);\n");
  printf("a2: %d\n\n", a2); // a2 remains 42

  int a3 = 10;
  printf("int a3 = %d;\n", a3);
  f3(&a3);
  printf("f3(&a3);\n");
  printf("a3: %d\n\n", a3); // a3 remains 10

  int a4 = 10;
  printf("int a4 = %d;\n", a4);
  f4(&a4);
  printf("f4(&a4);\n");
  printf("a4: %d\n\n", a4); // a4 remains 10

  print_message("Hello, World!"); // This line will cause a runtime error

  char msg[] = "Hello, World!";
  print_message(msg);
  printf("print_message(msg);\n");
  printf("msg: %s\n\n", msg); // msg remains "Hello, World!"

  return EXIT_SUCCESS;
}
