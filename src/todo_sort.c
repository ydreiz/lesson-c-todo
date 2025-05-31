#include <stdlib.h>
#include <string.h>

#include "todo_sort.h"

/**
 * Compare todos by ID ascending of qsort.
 * Returns negative if a < b, zero if equal, positive if a > b.
 */
int todo_compare_id_asc(const Todo *a, const Todo *b) { return (a->id > b->id) - (a->id < b->id); }
int todo_compare_id_desc(const Todo *a, const Todo *b) { return -todo_compare_id_asc(a, b); }

/**
 * Compare todos by status ascending of qsort.
 * Returns negative if a < b, zero if equal, positive if a > b.
 */
int todo_compare_status_asc(const Todo *a, const Todo *b) { return (a->done > b->done) - (a->done < b->done); }
int todo_compare_status_desc(const Todo *a, const Todo *b) { return -todo_compare_status_asc(a, b); }

/**
 * Compare todos by title ascending of qsort.
 * Returns negative if a < b, zero if equal, positive if a > b.
 */
int todo_compare_title_asc(const Todo *a, const Todo *b) { return strcmp(a->title, b->title); }
int todo_compare_title_desc(const Todo *a, const Todo *b) { return -todo_compare_title_asc(a, b); }

void todo_list_sort(TodoComparator cmp, TodoList *todos)
{
  if (!todos || !todos->data || todos->size == 0)
  {
    return;
  }
  qsort(todos->data, todos->size, sizeof(Todo), (int (*)(const void *, const void *))cmp);
}
