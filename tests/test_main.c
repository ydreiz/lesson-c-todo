
#include "../include/test.h"
#include <stdlib.h>

bool test_status_str(void);
bool test_add_todo_increases_count(void);
bool test_delete_todo_removes_item(void);
bool test_toggle_todo_status_changes_value(void);
bool test_edit_todo_title_change_title(void);

bool test_save_and_load_todos(void);
bool test_load_nonexistent_file(void);

int main(void) {
  run_test("Status string representation", test_status_str);
  run_test("Add Todo increases count", test_add_todo_increases_count);
  run_test("Delete Todo removes item", test_delete_todo_removes_item);
  run_test("Toggle Todo status changes value",
           test_toggle_todo_status_changes_value);
  run_test("Change Todo title", test_edit_todo_title_change_title);

  run_test("Save and Load Todos", test_save_and_load_todos);
  run_test("Load Nonexistent File", test_load_nonexistent_file);

  return EXIT_SUCCESS;
}
