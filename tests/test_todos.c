#include <stdbool.h>
#include <stdlib.h>

void run_test_errors(void);
void run_test_todo(void);
void run_test_todo_filter(void);
void run_test_todo_list(void);
void run_test_todo_sort(void);
void run_test_utils(void);
void run_test_tui(void);
void run_test_todo_store_simple(void);

int main(void)
{
  run_test_utils();
  run_test_errors();
  run_test_todo();
  run_test_todo_filter();
  run_test_todo_sort();
  run_test_todo_list();
  run_test_tui();
  run_test_todo_store_simple();

  return EXIT_SUCCESS;
}
