#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <stddef.h>

#include "todo_common.h"

TodoList *todo_list_create(size_t capacity);

TodoResult todo_list_resize(TodoList *todos);

void todo_list_free(TodoList **todos);

void todo_list_recalculate_next_id(TodoList *todos);

TodoResult todo_list_add(TodoList *todos, const Todo todo);

TodoResult todo_list_delete(TodoList *todos, size_t id);

#endif // !TODO_LIST_H
