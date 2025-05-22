#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

bool save_todos(const char *filename, const Todo todos[], size_t count) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    return false;
  }

  for (int i = 0; i < count; i++) {
    fprintf(fp, "%lu;%s;%d\n", todos[i].id, todos[i].title,
            todos[i].done ? 1 : 0);
  }
  fclose(fp);
  return true;
}

int load_todos(const char *filename, Todo **todos, size_t *capacity) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    return 0;
  }

  int count = 0;
  char line[256];
  while (fgets(line, sizeof(line), fp)) {
    if (count == *capacity) {
      *capacity *= 2;
      Todo *tmp = realloc(*todos, *capacity * sizeof(Todo));
      if (!tmp) {
        fprintf(stderr, "An error occurred while allocating "
                        "memory for the todo list\n");
        fclose(fp);
        return count;
      }
      *todos = tmp;
    }

    size_t id;
    char title[TITLE_SIZE];
    int done;
    if (sscanf(line, "%lu;%99[^;];%d", &id, title, &done) == 3) {
      (*todos)[count].id = id;
      strcpy((*todos)[count].title, title);
      (*todos)[count].done = done != 0;
      count++;
    }
  }
  fclose(fp);
  return count;
}
