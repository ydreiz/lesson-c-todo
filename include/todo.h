#ifndef TODO_H
#define TODO_H

#include <stdbool.h>
#include <stddef.h>

#define TODO_PATH "todos.txt"
#define TITLE_SIZE 100

typedef struct {
  size_t id;
  char title[TITLE_SIZE];
  bool done;
} Todo;

int add_todo(Todo **todos, int count, size_t *gloabl_id, size_t *capacity);
bool delete_todo(Todo todos[], int *count, size_t id);
bool toggle_todo_status(Todo todos[], int count, size_t id);
bool edit_todo_title(Todo todos[], int count, size_t id);
void print_todos(const Todo todos[], int count);

void clear_stdin(void);
const char *status_str(bool done);
bool input_title(char *buf, int size, const char *prompt);
bool input_status(void);

bool save_todos(const char *filename, const Todo todos[], size_t count);
int load_todos(const char *filename, Todo **todos, size_t *capacity);

#endif // !TODO_H
