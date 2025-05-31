#ifndef TODO_COMMON_H
#define TODO_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "utils.h"

#define TODO_VERSION "0.0.1"
#define INITIAL_CAPACITY 3
#define TODO_FILE "todos.txt"

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

typedef struct
{
  size_t id;
  u_string *title;
  bool done;
} Todo;

typedef struct
{
  Todo *data;
  size_t size;
  size_t next_id;
  size_t capacity;
} TodoList;

#endif // !TODO_COMMON_H
