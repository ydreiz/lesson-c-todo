#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"
#include "todo_list.h"
#include "utils.h"

TodoResult todo_add(const u_string *title, bool status, TodoList *todos)
{
  Todo todo = {.id = todos->next_id, .done = status, .title = u_strdup(title)};
  TodoResult res = todo_list_add(todos, todo);
  if (res != TODO_OK)
  {
    free(todo.title);
    return res;
  }
  return TODO_OK;
}

TodoResult todo_delete(TodoList *todos, size_t pos)
{
  if (!todos || !todos->data)
  {
    return TODO_ERR_EMPTY;
  }
  else if (pos >= todos->size)
  {
    return TODO_ERR_OUT_OF_BOUNDS;
  }
  u_strdup_free(todos->data[pos].title);
  for (size_t i = pos; i < todos->size - 1; i++)
  {
    todos->data[i] = todos->data[i + 1];
  }
  todos->size--;
  return TODO_OK;
}

TodoResult todo_toggle_status(TodoList *todos, size_t pos)
{
  if (!todos || !todos->data)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  else if (pos >= todos->size)
  {
    return TODO_ERR_OUT_OF_BOUNDS;
  }
  todos->data[pos].done = !todos->data[pos].done;
  return TODO_OK;
}

TodoResult todo_change_title(const char *title, TodoList *todos, size_t pos)
{
  if (!todos || !todos->data)
  {
    return TODO_ERR_EMPTY;
  }
  else if (pos > todos->size)
  {
    return TODO_ERR_NOT_FOUND;
  }
  u_strdup_free(todos->data[pos].title);
  if (!(todos->data[pos].title = u_strdup(title)))
  {
    return TODO_ERR_ALLOC;
  }
  return TODO_OK;
}

TodoResult todo_find_idx(const TodoList *todos, size_t id, size_t *pos)
{
  if (!todos->data || !pos)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  if (todos->size == 0)
  {
    return TODO_ERR_EMPTY;
  }
  for (size_t i = 0; i < todos->size; i++)
  {
    if (todos->data[i].id == id)
    {
      *pos = i;
      return TODO_OK;
    }
  }
  return TODO_ERR_NOT_FOUND;
}

TodoResult todo_deep_clone(Todo *dst, const Todo src)
{
  dst->id = src.id;
  dst->done = src.done;
  dst->title = u_strdup(src.title);
  if (!dst->title)
  {
    return TODO_ERR_ALLOC;
  }
  return TODO_OK;
}
