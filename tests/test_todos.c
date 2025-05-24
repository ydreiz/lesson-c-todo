#include "../include/test.h"
#include <stdlib.h>

bool test_add_todo_increases_count(void);
bool test_add_todo_failure_realloc(void);

bool test_find_todo_by_id(void);
bool test_find_todo_by_id_not_found(void);
bool test_find_todo_by_id_todos_empty(void);
bool test_find_todo_by_id_todos_null(void);
bool test_find_todo_by_id_pos_null(void);

bool test_delete_todo_removes_item(void);
bool test_delete_todo_removes_item_out_of_bounds(void);
bool test_delete_todo_removes_item_todos_null(void);
bool test_delete_todo_removes_item_count_null(void);

bool test_toggle_todo_status_changes_value(void);
bool test_toggle_todo_status_changes_value_todos_null(void);

bool test_change_todo_title(void);
bool test_change_todo_title_todos_null(void);
bool test_change_todo_title_null(void);

bool test_save_and_load_todos(void);
bool test_load_nonexistent_file(void);

int main(void)
{
  run_test("Add Todo increases count", test_add_todo_increases_count);
  run_test("Add Todo invalid realloc", test_add_todo_failure_realloc);

  run_test("Find Todo by ID", test_find_todo_by_id);
  run_test("Find Todo by ID not found", test_find_todo_by_id_not_found);
  run_test("Find Todo by ID when todos are empty", test_find_todo_by_id_todos_empty);
  run_test("Find Todo by ID when todos is NULL", test_find_todo_by_id_todos_null);
  run_test("Find Todo by ID when pos is NULL", test_find_todo_by_id_pos_null);

  run_test("Delete Todo removes item", test_delete_todo_removes_item);
  run_test("Delete Todo removes item out of bounds", test_delete_todo_removes_item_out_of_bounds);
  run_test("Delete Todo removes item when todos is NULL", test_delete_todo_removes_item_todos_null);
  run_test("Delete Todo removes item when count is NULL", test_delete_todo_removes_item_count_null);

  run_test("Toggle Todo status changes value", test_toggle_todo_status_changes_value);
  run_test("Toggle Todo status changes value when todos is NULL", test_toggle_todo_status_changes_value_todos_null);

  run_test("Change Todo title", test_change_todo_title);
  run_test("Change Todo title when todos is NULL", test_change_todo_title_todos_null);
  run_test("Change Todo title when title is NULL", test_change_todo_title_null);

  run_test("Save and Load Todos", test_save_and_load_todos);
  run_test("Load Nonexistent File", test_load_nonexistent_file);

  return EXIT_SUCCESS;
}
