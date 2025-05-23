#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

TodoResult save_todos(const char *filename, const Todo todos[], size_t *count) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    return TODO_ERR_FILE;
  }

  for (int i = 0; i < *count; i++) {
    fprintf(fp, "%lu;%s;%d\n", todos[i].id, todos[i].title,
            todos[i].done ? 1 : 0);
  }
  fclose(fp);

  return TODO_OK;
}

TodoResult load_todos(const char *filename, Todo **todos, size_t *capacity,
                      size_t *count) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    return TODO_ERR_FILE;
  }

  char line[256];
  while (fgets(line, sizeof(line), fp)) {
    if (*count == *capacity) {
      *capacity *= 2;
      Todo *tmp = realloc(*todos, *capacity * sizeof(Todo));
      if (!tmp) {
        fprintf(stderr, "An error occurred while allocating "
                        "memory for the todo list\n");
        fclose(fp);
        return TODO_ERR_ALLOC;
      }
      *todos = tmp;
    }

    size_t id;
    char title[TITLE_SIZE];
    int done;
    if (sscanf(line, "%lu;%99[^;];%d", &id, title, &done) == 3) {
      (*todos)[*count].id = id;
      strcpy((*todos)[*count].title, title);
      (*todos)[*count].done = done != 0;
      (*count)++;
    }
  }
  fclose(fp);

  return TODO_OK;
}
