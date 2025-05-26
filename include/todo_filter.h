#ifndef TODO_FILTER_H
#define TODO_FILTER_H

#include <stdbool.h>

#include "todo.h"

bool todo_is_done(const Todo todo);

bool todo_is_not_done(const Todo todo);

#endif // !TODO_FILTER_H
