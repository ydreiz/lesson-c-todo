#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "todo.h"
#include "todo_common.h"
#include "todo_filter.h"
#include "todo_list.h"

bool todo_is_done(const Todo todo, va_list args) { return todo.done; }

bool todo_is_not_done(const Todo todo, va_list args) { return !todo.done; }

bool todo_find_by_id(const Todo todo, va_list args)
{
  size_t id = va_arg(args, size_t);
  return todo.id == id;
}

TodoResult todo_list_filter(TodoFilterFn fn, const TodoList *src_todos, TodoList *dest_todos, ...)
{
  if (!src_todos || !dest_todos || !src_todos->data || !dest_todos->data)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  dest_todos->size = 0;
  size_t max_id = 1;
  for (size_t i = 0; i < src_todos->size; i++)
  {
    va_list args;
    va_start(args, dest_todos);
    if (fn(src_todos->data[i], args))
    {
      TodoResult res = todo_list_resize(dest_todos);
      if (res != TODO_OK && res != TODO_NOTHING)
      {
        va_end(args);
        return TODO_ERR_ALLOC;
      }
      if (todo_deep_clone(&dest_todos->data[dest_todos->size], src_todos->data[i]) == TODO_ERR_ALLOC)
      {
        va_end(args);
        return TODO_ERR_ALLOC;
      }
      dest_todos->size++;
      if (src_todos->data[i].id > max_id)
      {
        max_id = src_todos->data[i].id;
      }
    }
    va_end(args);
  }
  // INFO: Used only for drawing tasks, affects indentation within the id
  dest_todos->next_id = max_id + 1;
  return TODO_OK;
}

Todo *todo_list_find(TodoFilterFn fn, const TodoList *todos, ...)
{
  if (!todos || !todos->data)
  {
    return NULL;
  }
  for (size_t i = 0; i < todos->size; i++)
  {
    va_list args;
    va_start(args, todos);
    if (fn(todos->data[i], args))
    {
      va_end(args);
      return &todos->data[i];
    }
    va_end(args);
  }
  return NULL;
}
