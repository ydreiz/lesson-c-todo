#ifndef TODO_H
#define TODO_H

#include <stdbool.h>
#include <stddef.h>

#define TODO_FILE "todos.txt"

typedef struct
{
  size_t id;
  char title[100];
  bool done;
} Todo;

typedef struct
{
  Todo *data;
  size_t size;
  size_t next_id;
  size_t capacity;
} TodoList;

typedef enum
{
  TODO_NOTHING = -1,
  TODO_OK = 0,
  TODO_ERR_ALLOC = 201,
  TODO_ERR_NOT_FOUND = 202,
  TODO_ERR_EMPTY = 203,
  TODO_ERR_FILE = 301,
  TODO_ERR_OUT_OF_BOUNDS = 401,
  TODO_ERR_INVALID_ARGUMENT = 501,
} TodoResult;

TodoResult todo_add(const char *title, bool status, TodoList *todos);

TodoResult todo_delete(TodoList *todos, size_t pos);

TodoResult todo_toggle_status(TodoList *todos, size_t pos);

TodoResult todo_change_title(const char *title, TodoList *todos, size_t pos);

TodoResult todo_find(const TodoList *todos, size_t id, size_t *pos);

TodoResult todo_save(const char *filename, const TodoList *todos);

TodoResult todo_load(const char *filename, TodoList *todos);

TodoResult todo_filter(const TodoList *src_todos, TodoList *dest_todos, bool done);

TodoList *todo_list_create(size_t capacity);

TodoResult todo_list_resize(TodoList *todos);

void todo_list_destroy(TodoList **todos);

void todo_recalculate_next_id(TodoList *todos);

#endif // !TODO_H
