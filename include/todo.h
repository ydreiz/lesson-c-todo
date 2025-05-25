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
  Todo *todos;
  size_t size;
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

TodoResult todo_add(const char *title, bool status, Todo *todos[], size_t *count, size_t *global_id, size_t *capacity);

TodoResult todo_delete(Todo todos[], size_t *count, size_t pos);

TodoResult todo_toggle_status(Todo todos[], size_t pos);

TodoResult todo_change_title(const char *title, Todo todos[], size_t pos);

TodoResult todo_find(const Todo todos[], size_t count, size_t id, size_t *pos);

TodoResult todo_save(const char *filename, const Todo todos[], size_t count);

TodoResult todo_load(const char *filename, Todo *todos[], size_t *capacity, size_t *count);

TodoList *todo_list_create(size_t initial_capacity);

TodoResult todo_list_resize(TodoList *list);

void todo_list_destroy(TodoList **list);

#endif // !TODO_H
