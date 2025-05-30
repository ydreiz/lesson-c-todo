#ifndef TODO_FILTER_H
#define TODO_FILTER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "todo_common.h"

typedef bool (*TodoFilterFn)(const Todo todo, va_list args);

bool todo_is_done(const Todo todo, va_list args);

bool todo_is_not_done(const Todo todo, va_list args);

bool todo_find_by_id(const Todo todo, va_list args);

TodoResult todo_list_filter(TodoFilterFn, const TodoList *src_todos, TodoList *dest_todos, ...);

Todo *todo_list_find(TodoFilterFn fn, const TodoList *todos, ...);

#endif // !TODO_FILTER_H
