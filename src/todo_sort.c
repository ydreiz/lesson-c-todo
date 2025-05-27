#include <string.h>

#include "todo.h"
#include "todo_sort.h"

int todo_compare_id_asc(const void *a, const void *b)
{
  const Todo *todo_a = (const Todo *)a;
  const Todo *todo_b = (const Todo *)b;
  return (todo_a->id > todo_b->id) - (todo_a->id < todo_b->id);
}
int todo_compare_id_desc(const void *a, const void *b) { return -todo_compare_id_asc(a, b); }

int todo_compare_status_asc(const void *a, const void *b)
{
  const Todo *todo_a = (const Todo *)a;
  const Todo *todo_b = (const Todo *)b;
  return (todo_a->done > todo_b->done) - (todo_a->done < todo_b->done);
}
int todo_compare_status_desc(const void *a, const void *b) { return -todo_compare_status_asc(a, b); }

int todo_compare_title_asc(const void *a, const void *b)
{
  const Todo *todo_a = (const Todo *)a;
  const Todo *todo_b = (const Todo *)b;
  return strcmp(todo_a->title, todo_b->title);
}
int todo_compare_title_desc(const void *a, const void *b) { return -todo_compare_title_asc(a, b); }
