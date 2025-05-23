#include <stdio.h>

#include "print.h"

void print_success(char *msg) { fprintf(stdout, "\n[Success] %s\n\n", msg); }

void print_notify(char *msg) { fprintf(stdout, "\n[Notify] %s\n\n", msg); }

void print_error(char *nsg) { fprintf(stderr, "\n[Error] %s\n\n", nsg); }
