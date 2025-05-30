#ifndef TODO_STORE_SIMPLE_H
#define TODO_STORE_SIMPLE_H

#include "todo_common.h"

TodoResult todo_save(const char *filename, const TodoList *todos);

TodoResult todo_load(const char *filename, TodoList *todos);

#endif // !TODO_STORE_SIMPLE_H
