#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "print.h"

void print_success(const char *msg) { fprintf(stdout, "\n[Success] %s\n", msg); }

void print_notify(const char *msg) { fprintf(stdout, "\n[Notify] %s\n", msg); }

void print_error(const char *msg)
{
  fprintf(stderr, "[ERRO] %s: %s\n\n", msg, strerror(errno));
  perror(NULL);
}
