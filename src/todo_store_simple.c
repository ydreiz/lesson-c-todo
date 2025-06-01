#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo_common.h"
#include "todo_list.h"
#include "todo_store_simple.h"
#include "utils.h"

long file_size(FILE *file)
{
  if (!file)
  {
    return -1;
  }
  if (fseek(file, 0, SEEK_END) != 0)
  {
    return -1;
  }
  long size = ftell(file);
  if (size == -1)
  {
    return -1;
  }
  rewind(file);
  return size;
}

char *fille_contents(const char *path)
{
  FILE *fp = fopen(path, "r");
  if (!fp)
  {
    return NULL;
  }
  long f_size = file_size(fp);
  if (f_size < 0)
  {
    fclose(fp);
    return NULL;
  }
  char *buf = malloc(f_size + 1);
  if (!buf)
  {
    fclose(fp);
    return NULL;
  }
  size_t r_size = fread(buf, 1, f_size, fp);
  if (r_size != f_size)
  {
    free(buf);
    fclose(fp);
    return NULL;
  }
  buf[r_size] = '\0';
  return buf;
}

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
  char *contents = fille_contents(filename);
  if (!contents)
  {
    return TODO_ERR_FILE;
  }
  char *line = strtok(contents, "\n");
  while (line)
  {
    TodoResult result = todo_list_resize(todos);
    if (result != TODO_NOTHING && result != TODO_OK)
    {
      free(contents);
      return TODO_ERR_ALLOC;
    }
    // Parse the line
    // Format: id;title;done
    size_t id;
    char title[100];
    int done;
    if (sscanf(line, "%lu;%99[^;];%d", &id, title, &done) != 3)
    {
      free(contents);
      return TODO_ERR_FILE;
    }
    todos->data[todos->size++] = (Todo){.id = id, .title = u_strdup(title), .done = done == 1};
    line = strtok(NULL, "\n");
  }
  free(contents);
  return TODO_OK;
}
