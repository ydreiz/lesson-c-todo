#ifndef TODO_H
#define TODO_H

#include <stdbool.h>
#include <stddef.h>

#define TODO_PATH "todos.txt"
#define TITLE_SIZE 100

typedef enum {
  TODO_OK = 0,

  TODO_CHOSE_AGREE = 101,
  TODO_CHOSE_REJECT = 102,

  TODO_ERR_ALLOC = 201,
  TODO_ERR_NOT_FOUND = 202,
  TODO_ERR_INVALID_INPUT = 203,
  TODO_ERR_EMPTY_INPUT = 204,

  TODO_ERR_FILE = 301,
  TODO_ERR_FILE_WRITE = 302,
  TODO_ERR_FILE_READ = 303,
  TODO_ERR_FILE_CLOSE = 304,
} TodoResult;

typedef struct {
  size_t id;
  char title[TITLE_SIZE];
  bool done;
} Todo;

TodoResult add_todo(Todo **todos, size_t *count, size_t *gloabl_id,
                    size_t *capacity);
TodoResult delete_todo(Todo todos[], size_t *count, size_t id);
TodoResult toggle_todo_status(Todo todos[], size_t count, size_t id);
TodoResult edit_todo_title(Todo todos[], size_t count, size_t id);
void print_todos(const Todo todos[], size_t count);

TodoResult input_title(char *buf, int size, const char *prompt);
TodoResult input_status(void);

TodoResult save_todos(const char *filename, const Todo todos[], size_t *count);
TodoResult load_todos(const char *filename, Todo **todos, size_t *capacity,
                      size_t *count);

const char *status_str(bool done);
void clear_stdin(void);

#endif // !TODO_H
