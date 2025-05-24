#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

TodoResult todo_add(const char *title, bool status, Todo *todos[], size_t *count, size_t *global_id, size_t *capacity)
{
  if (*count >= *capacity)
  {
    *capacity *= 2;
    Todo *todos_t = realloc(*todos, *capacity * sizeof(Todo));
    if (!todos_t)
    {
      return TODO_ERR_ALLOC;
    }
    *todos = todos_t;
  }

  Todo todo;
  todo.id = ++(*global_id);
  todo.done = status;
  strcpy(todo.title, title);

  (*todos)[*count] = todo;
  (*count)++;

  return TODO_OK;
}

TodoResult todo_delete(Todo todos[], size_t *count, size_t pos)
{
  if (todos == NULL || count == NULL)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }

  if (pos >= *count)
  {
    return TODO_ERR_OUT_OF_BOUNDS;
  }

  for (size_t i = pos; i < *count - 1; i++)
  {
    todos[i] = todos[i + 1];
  }

  (*count)--;

  return TODO_OK;
}

TodoResult todo_toggle_status(Todo todos[], size_t pos)
{
  if (todos == NULL)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }

  todos[pos].done = !todos[pos].done;

  return TODO_OK;
}

TodoResult todo_change_title(const char *title, Todo todos[], size_t pos)
{
  if (todos == NULL || title == NULL)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }

  strcpy(todos[pos].title, title);

  return TODO_OK;
}

TodoResult todo_find(const Todo todos[], size_t count, size_t id, size_t *pos)
{
  if (todos == NULL || pos == NULL)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }

  if (count == 0)
  {
    return TODO_ERR_EMPTY;
  }

  for (size_t i = 0; i < count; i++)
  {
    if (todos[i].id == id)
    {
      *pos = i;
      return TODO_OK;
    }
  }

  return TODO_ERR_NOT_FOUND;
}
