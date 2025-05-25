#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

TodoResult todo_save(const char *filename, const TodoList *todos)
{
  FILE *fp = fopen(filename, "w");
  if (!fp)
  {
    return TODO_ERR_FILE;
  }

  for (size_t i = 0; i < todos->size; i++)
  {
    Todo todo = todos->data[i];
    int result = fprintf(fp, "%lu;%s;%d\n", todo.id, todo.title, todo.done ? 1 : 0);
    if (result < 0)
    {
      if (ferror(fp))
      {
        fclose(fp);
        return TODO_ERR_FILE;
      }
      fclose(fp);
      return TODO_ERR_FILE;
    }
  }

  if (fclose(fp) != 0)
  {
    return TODO_ERR_FILE;
  }

  return TODO_OK;
}

TodoResult todo_load(const char *filename, TodoList *todos)
{
  FILE *fp = fopen(filename, "r");
  if (!fp)
  {
    return TODO_ERR_FILE;
  }

  char line[256];
  while (fgets(line, sizeof(line), fp))
  {
    TodoResult result = todo_list_resize(todos);
    if (result != TODO_NOTHING && result != TODO_OK)
    {
      return TODO_ERR_ALLOC;
    }

    size_t id;
    char title[100];
    int done;
    if (sscanf(line, "%lu;%99[^;];%d", &id, title, &done) == 3)
    {
      todos->data[todos->size].id = id;
      strcpy(todos->data[todos->size].title, title);
      todos->data[todos->size].done = done != 0;
      todos->size++;
    }
  }

  if (ferror(fp))
  {
    fclose(fp);
    return TODO_ERR_FILE;
  }
  else if (fclose(fp) != 0)
  {
    return TODO_ERR_FILE;
  }
  return TODO_OK;
}
