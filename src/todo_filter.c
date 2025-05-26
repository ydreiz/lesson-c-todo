#include <stdbool.h>

#include "todo.h"
#include "todo_filter.h"

bool todo_is_done(const Todo todo) { return todo.done; }

bool todo_is_not_done(const Todo todo) { return !todo.done; }
