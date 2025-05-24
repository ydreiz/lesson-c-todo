#include <stdio.h>

#include "print.h"

void print_success(const char *msg) {
  fprintf(stdout, "\n[Success] %s\n\n", msg);
}

void print_notify(const char *msg) {
  fprintf(stdout, "\n[Notify] %s\n\n", msg);
}

void print_error(const char *msg) { fprintf(stderr, "\n[Error] %s\n\n", msg); }
