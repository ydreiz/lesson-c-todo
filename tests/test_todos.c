#include <stdlib.h>

#include "test.h"

bool test_todos_list_create(void);
bool test_todos_list_create_null(void);
bool test_todos_list_create_failure(void);

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

bool test_toggle_todo_status_changes_value(void);
bool test_toggle_todo_status_changes_todos_null(void);
bool test_toggle_todo_status_changes_value_null(void);
bool test_toggle_todo_status_changes_out_of_bounds(void);

bool test_change_todo_title(void);
bool test_change_todo_title_todos_null(void);
bool test_change_todo_title_not_foudn(void);
bool test_change_todo_title_todos_data_null(void);

bool test_save_and_load_todos(void);
bool test_load_nonexistent_file(void);

bool test_tui_input_text_successfuly(void);
bool test_tui_input_text_empty(void);
bool test_tui_input_text_eof(void);

bool test_tui_input_number_successfuly(void);
bool test_tui_input_number_invalid(void);
bool test_tui_input_number_eof(void);

bool test_tui_print_todos(void);

int main(void)
{
  run_test("Todos List Create", test_todos_list_create);
  run_test("Todos List Create Null", test_todos_list_create_null);
  run_test("Todos List Create Failure", test_todos_list_create_failure);

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

  run_test("Toggle Todo status changes value", test_toggle_todo_status_changes_value);
  run_test("Toggle Todo status changes todos is NULL", test_toggle_todo_status_changes_todos_null);
  run_test("Toggle Todo status changes value is NULL", test_toggle_todo_status_changes_value_null);
  run_test("Toggle Todo status changes out of bounds", test_toggle_todo_status_changes_out_of_bounds);

  run_test("Change Todo title", test_change_todo_title);
  run_test("Change Todo title when todos is NULL", test_change_todo_title_todos_null);
  run_test("Change Todo title when todos is empty", test_change_todo_title_not_foudn);
  run_test("Change Todo title when todos data is NULL", test_change_todo_title_todos_data_null);

  run_test("Save and Load Todos", test_save_and_load_todos);
  run_test("Load Nonexistent File", test_load_nonexistent_file);

  run_test("TUI Input Text Successfuly", test_tui_input_text_successfuly);
  run_test("TUI Input Text Empty", test_tui_input_text_empty);
  run_test("TUI Input Text EOF", test_tui_input_text_eof);

  run_test("TUI Input Number Successfuly", test_tui_input_number_successfuly);
  run_test("TUI Input Number Invalid", test_tui_input_number_invalid);
  run_test("TUI Input Number EOF", test_tui_input_number_eof);

  run_test("TUI Print Todos", test_tui_print_todos);

  return EXIT_SUCCESS;
}
