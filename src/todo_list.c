#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"
#include "todo_common.h"
#include "todo_list.h"

TodoList *todo_list_create(size_t capacity)
{
  TodoList *todos = calloc(1, sizeof(TodoList));
  if (todos == NULL)
  {
    return NULL;
  }
  if (capacity == 0)
  {
    capacity = INITIAL_CAPACITY;
  }
  if (capacity > SIZE_MAX / sizeof(Todo))
  {
    free(todos);
    return NULL;
  }
  todos->data = calloc(capacity, sizeof(Todo));
  if (todos->data == NULL)
  {
    free(todos);
    return NULL;
  }
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
  if (todos->capacity > SIZE_MAX / sizeof(Todo))
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

TodoResult todo_list_shrink(TodoList *todos)
{
  if (!todos || !todos->data)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  // If the fill is less than 25%, we shrink it.
  float fill = (float)todos->size / (float)todos->capacity;
  if (fill >= 0.25f)
  {
    return TODO_NOTHING;
  }
  size_t new_capacity = (todos->size == 0) ? INITIAL_CAPACITY : todos->size * 2;
  if (new_capacity >= todos->capacity)
  {
    return TODO_NOTHING;
  }
  Todo *tmp = realloc(todos->data, new_capacity * sizeof(Todo));
  if (!tmp && new_capacity > 0)
  {
    return TODO_ERR_ALLOC;
  }
  todos->data = tmp;
  todos->capacity = new_capacity;
  return TODO_OK;
}

void todo_list_free(TodoList **todos)
{
  if (todos && *todos)
  {
    for (size_t i = 0; i < (*todos)->size; i++)
    {
      if ((*todos)->data[i].title)
      {
        u_strdup_free((*todos)->data[i].title);
        (*todos)->data[i].title = NULL;
      }
    }
    free((*todos)->data);
    (*todos)->data = NULL;

    free(*todos);
    *todos = NULL;
  }
}

void todo_list_recalculate_next_id(TodoList *todos)
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

TodoResult todo_list_add(TodoList *todos, const Todo todo)
{
  if (!todos || !todos->data)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  if (todos->size >= todos->capacity)
  {
    TodoResult res = todo_list_resize(todos);
    if (res != TODO_OK)
    {
      return res;
    }
  }
  todos->data[todos->size] = todo;
  todos->data[todos->size].id = todos->next_id++;
  todos->size++;
  return TODO_OK;
}

TodoResult todo_list_delete(TodoList *todos, size_t id)
{
  if (!todos || !todos->data)
  {
    return TODO_ERR_INVALID_ARGUMENT;
  }
  if (todos->size == 0)
  {
    return TODO_ERR_EMPTY;
  }
  size_t pos = -1;
  if (todo_find_idx(todos, id, &pos) != TODO_OK)
  {
    return TODO_ERR_NOT_FOUND;
  }
  if (pos == SIZE_MAX)
  {
    return TODO_ERR_NOT_FOUND;
  }
  TodoResult res = todo_delete(todos, pos);
  if (res == TODO_OK)
  {
    todo_list_shrink(todos);
  }
  return res;
}
