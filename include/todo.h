#ifndef TODO_H
#define TODO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "todo_common.h"
#include "utils.h"

TodoResult todo_add(const u_string *title, bool status, TodoList *todos);

TodoResult todo_delete(TodoList *todos, size_t pos);

TodoResult todo_toggle_status(TodoList *todos, size_t pos);

TodoResult todo_change_title(const u_string *title, TodoList *todos, size_t pos);

TodoResult todo_find_idx(const TodoList *todos, size_t id, size_t *pos);

TodoResult todo_deep_clone(Todo *dst, const Todo src);

#endif // !TODO_H
