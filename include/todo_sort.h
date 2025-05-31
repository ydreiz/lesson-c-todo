#ifndef TODO_SORT_H
#define TODO_SORT_H

#include "todo_common.h"

typedef int (*TodoComparator)(const Todo *a, const Todo *b);

int todo_compare_status_asc(const Todo *a, const Todo *b);
int todo_compare_status_desc(const Todo *a, const Todo *b);

int todo_compare_id_asc(const Todo *a, const Todo *b);
int todo_compare_id_desc(const Todo *a, const Todo *b);

int todo_compare_title_asc(const Todo *a, const Todo *b);
int todo_compare_title_desc(const Todo *a, const Todo *b);

void todo_list_sort(TodoComparator cmp, TodoList *todos);

#endif // !TODO_SORT_H
