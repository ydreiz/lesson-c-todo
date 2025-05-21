#ifndef TODO_H
#define TODO_H

#include <stdbool.h>

#define TITLE_SIZE 100
#define MAX_TODOS 10

typedef struct {
  unsigned int id;
  char title[TITLE_SIZE];
  bool done;
} Todo;

int add_todo(Todo todos[], int capacity, int count, unsigned int *gloabl_id);
bool delete_todo(Todo todos[], int *count, unsigned int id);
bool toggle_todo_status(Todo todos[], int count, unsigned int id);
void print_todos(Todo todos[], int count);

void clear_stdin(void);
const char *status_str(bool done);
bool input_title(char *buf, int size);
bool input_status(void);

bool save_todos(const char *filename, Todo todos[], int count);
int load_todos(const char *filename, Todo todos[], int capacity);

#endif // !TODO_H
