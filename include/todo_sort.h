#ifndef TODO_SORT_H
#define TODO_SORT_H

#include "todo_common.h"

int todo_compare_status_asc(const void *, const void *);
int todo_compare_status_desc(const void *, const void *);

int todo_compare_id_asc(const void *, const void *);
int todo_compare_id_desc(const void *, const void *);

int todo_compare_title_asc(const void *, const void *);
int todo_compare_title_desc(const void *, const void *);

void todo_list_sort(int (*cmp)(const void *, const void *), TodoList *todos);

#endif // !TODO_SORT_H
