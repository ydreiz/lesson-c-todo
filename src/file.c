#include "todo.h"
#include <stdio.h>
#include <string.h>

bool save_todos(const char *filename, Todo todos[], int count) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    return false;
  }

  for (int i = 0; i < count; i++) {
    fprintf(fp, "%u;%s;%d\n", todos[i].id, todos[i].title,
            todos[i].done ? 1 : 0);
  }
  fclose(fp);
  return true;
}

int load_todos(const char *filename, Todo todos[], int capacity) {
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return 0;

  int count = 0;
  char line[256];
  while (fgets(line, sizeof(line), fp) && count < capacity) {
    unsigned int id;
    char title[TITLE_SIZE];
    int done_int;

    if (sscanf(line, "%u;%99[^;];%d", &id, title, &done_int) == 3) {
      todos[count].id = id;
      strcpy(todos[count].title, title);
      todos[count].done = done_int != 0;
      count++;
    }
  }
  fclose(fp);
  return count;
}
