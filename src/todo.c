#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

TodoList *todo_list_create(size_t capacity)
{
  TodoList *todos = malloc(sizeof(TodoList));
  if (!todos)
  {
    return NULL;
  }
  todos->data = malloc(capacity * sizeof(Todo));
  if (!todos->data)
  {
    free(todos);
    return NULL;
  }
  todos->size = 0;
  todos->capacity = capacity;
  todos->next_id = 1;
  return todos;
}

TodoResult todo_list_resize(TodoList *todos)
{
  if (!todos || !todos->data)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  else if (todos->capacity > todos->size)
  {
    return TODO_NOTHING;
  }
  else if (todos->capacity == 0)
  {
    return TODO_ERR_ALLOC;
  }
  size_t new_capacity = todos->capacity * 2;
  Todo *tmp = realloc(todos->data, new_capacity * sizeof(Todo));
  if (!tmp && new_capacity > 0)
  {
    return TODO_ERR_ALLOC;
  }
  todos->data = tmp;
  todos->capacity = new_capacity;
  return TODO_OK;
}

void todo_list_destroy(TodoList **todos_ptr)
{
  if (todos_ptr && *todos_ptr)
  {
    free((*todos_ptr)->data);
    (*todos_ptr)->data = NULL;

    free(*todos_ptr);
    *todos_ptr = NULL;
  }
}

TodoResult todo_add(const char *title, bool status, TodoList *todos)
{
  TodoResult res = todo_list_resize(todos);
  if (res != TODO_OK && res != TODO_NOTHING)
  {
    return TODO_ERR_ALLOC;
  }

  Todo todo;
  todo.id = todos->next_id++;
  todo.done = status;
  strcpy(todo.title, title);

  todos->data[todos->size] = todo;
  todos->size++;

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

  strcpy(todos->data[pos].title, title);

  return TODO_OK;
}

TodoResult todo_find(const TodoList *todos, size_t id, size_t *pos)
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

TodoResult todo_list_filter(bool (*fn)(const Todo todo), const TodoList *src_todos, TodoList *dest_todos)
{
  if (!src_todos || !dest_todos || !src_todos->data || !dest_todos->data)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  dest_todos->size = 0;

  for (size_t i = 0; i < src_todos->size; i++)
  {
    if (fn(src_todos->data[i]))
    {
      if (dest_todos->size >= dest_todos->capacity)
      {
        if (todo_list_resize(dest_todos) != TODO_OK)
        {
          return TODO_ERR_ALLOC;
        }
      }
      dest_todos->data[dest_todos->size++] = src_todos->data[i];
    }
  }
  return TODO_OK;
}

void todo_recalculate_next_id(TodoList *todos)
{
  if (!todos || !todos->data || todos->size == 0)
  {
    return;
  }
  size_t max_id = 0;
  for (size_t i = 0; i < todos->size; i++)
  {
    if (todos->data[i].id > max_id)
    {
      max_id = todos->data[i].id;
    }
  }
  todos->next_id = max_id + 1;
}
