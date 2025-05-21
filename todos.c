#include "stdbool.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_TODOS 10
#define S_TODOS_FILENAME "todos.txt"

unsigned int c_todos = 3;

int next_id(void) { return ++c_todos; }

typedef struct {
  unsigned int id;
  char title[100];
  bool done;
} Todo;

void clear_stdin(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    // ...
  }
}

const char *status_str(bool done) { return done ? "[x]" : "[ ]"; }

int status_str_file(bool done) { return done ? 1 : 0; }

void print_todos(Todo todos[], int c_todos) {
  for (int i = 0; i < c_todos; i++) {
    Todo todo = todos[i];
    if (c_todos < 10) {
      printf("[%d] %-50s %s\n", todo.id, todo.title, status_str(todo.done));
    } else if (c_todos >= 100) {
      printf("[%3d] %-48s %s\n", todo.id, todo.title, status_str(todo.done));
    } else {
      printf("[%2d] %-49s %s\n", todo.id, todo.title, status_str(todo.done));
    }
  }
}

bool input_title(char *buf, size_t size) {
  printf("New todo title: ");
  if (fgets(buf, size, stdin) == NULL) {
    printf("Error when enter title!\n");
    return false;
  }
  buf[strcspn(buf, "\n")] = '\0';
  return strlen(buf) > 0;
}

bool input_status() {
  char done[2];
  do {
    printf("Status is done [y/n] (Default: n): ");
    if (fgets(done, sizeof(done), stdin) == NULL) {
      printf("Error when read status!\n");
      return false;
    }
    done[strcspn(done, "\n")] = '\0';

    if (done[0] == '\0') {
      strcpy(done, "n");
    } else if (done[strlen(done) - 1] != '\n') {
      clear_stdin();
    }
  } while (strcmp(done, "n") != 0 && strcmp(done, "y") != 0);

  return strcmp(done, "y") == 0;
}

int add_todo(Todo *todos, int capacity, int c_todos) {
  if (capacity == c_todos) {
    printf("Todos list overflow, before add new todo, remove some todo!\n");
    return c_todos;
  }

  char title[100];
  if (!input_title(title, sizeof(title))) {
    return c_todos;
  }

  Todo todo;
  todo.done = input_status();
  todo.id = next_id();
  strcpy(todo.title, title);

  todos[c_todos] = todo;

  return c_todos + 1;
}

bool delete_todo(Todo todos[], int *c_todos, unsigned int t_id) {
  int pos = -1;
  for (int i = 0; i < *c_todos; i++) {
    if (todos[i].id == t_id) {
      pos = i;
      break;
    }
  }

  if (pos == -1) {
    return false;
  }

  for (int i = pos; i < *c_todos - 1; i++) {
    todos[i] = todos[i + 1];
  }
  (*c_todos) = (*c_todos) - 1;

  return true;
}

bool save_todos(const char *filename, Todo todos[], int c_todos) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    fprintf(stderr, "Todos ca't be saved to a file todos.txt\n");
    return false;
  }

  for (int i = 0; i < c_todos; i++) {
    int res = fprintf(fp, "%d;%s;%d\n", todos[i].id, todos[i].title,
                      status_str_file(todos[i].done));
    if (res < 0) {
      fprintf(stderr, "Error writing to todos.txt\n");
      fclose(fp);
      return false;
    }

    if (ferror(fp)) {
      fprintf(stderr, "Stream error detected at save to a todos.txt\n");
      fclose(fp);
      return false;
    }
  }
  fclose(fp);
  return true;
}

int load_todos(const char *filename, Todo todos[], int capacity) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Todos ca't be read from a file todos.txt\n");
    return 0;
  }

  int i = 0;
  char ln[255];
  while (fgets(ln, sizeof(ln), fp) != NULL) {
    if (i >= capacity) {
      fprintf(stderr, "Todos capacity exceeded, stop loading.\n");
      break;
    }

    ln[strcspn(ln, "\n")] = '\0';

    char *id_str = strtok(ln, ";");
    char *title = strtok(NULL, ";");
    char *done_str = strtok(NULL, ";");

    if (id_str && title && done_str) {
      todos[i].id = atoi(id_str);
      todos[i].done = strcmp(done_str, "1") == 0 ? true : false;
      strcpy(todos[i].title, title);
      i++;
    } else {
      fprintf(stderr, "An error occurred while reading todo!\n");
    }
  }

  fclose(fp);

  return i;
}

bool toggle_todo_status(Todo todos[], int c_todos, unsigned int id) {
  for (int i = 0; i < c_todos; i++) {
    if (todos[i].id == id) {
      todos[i].done = !todos[i].done;
      return true;
    }
  }
  return false;
}

int main(void) {
  Todo todos[S_TODOS];

  int c_todos = load_todos(S_TODOS_FILENAME, todos, S_TODOS);

  print_todos(todos, c_todos);

  do {
    int c_todos_next = c_todos;

    // Add todo
    do {
      if ((c_todos_next = add_todo(todos, S_TODOS, c_todos)) == 0) {
        break;
      }

      if (c_todos != 0 && c_todos_next == c_todos) {
        printf("No title entered. Stopping addition of tasks.\n");
        break;
      }
      c_todos = c_todos_next;
      print_todos(todos, c_todos);

    } while (true);

    if (c_todos == 0) {
      printf("Your list is empty, add a new todo!\n");
      continue;
    }

    print_todos(todos, c_todos);

    // Change status
    do {
      int t_id;
      printf("Enter todo ID than needs a status change (0: skip): ");
      scanf("%u", &t_id);
      clear_stdin();

      if (t_id == 0) {
        printf("Exit change status\n");
        break;
      }
      if (!toggle_todo_status(todos, c_todos, t_id)) {
        printf("Todo with ID %d not found.\n", t_id);
      }

      print_todos(todos, c_todos);
    } while (true);

    print_todos(todos, c_todos);

    // Dlete todo
    do {
      int t_id;
      printf("Enter todo ID than needs a delete (0: skip): ");
      scanf("%u", &t_id);
      clear_stdin();

      if (t_id == 0) {
        printf("Exit delete todo\n");
        break;
      }

      if (!delete_todo(todos, &c_todos, t_id)) {
        printf("Todo with ID %d not found.\n", t_id);
      }

      if (c_todos == 0) {
        break;
      }

      print_todos(todos, c_todos);
    } while (true);

    // Save todos
    do {
      char save[2];
      printf("Save todos for todos.txt [y/n]: ");
      fgets(save, sizeof(save), stdin);
      save[strcspn(save, "\n")] = '\0';

      if (save[0] == '\0') {
        strcpy(save, "n");
      } else if (save[strlen(save) - 1] != '\n') {
        clear_stdin();
      }

      if (strcmp(save, "y") == 0) {
        if (!save_todos(S_TODOS_FILENAME, todos, c_todos)) {
          fprintf(stderr, "There was an error when saving!\n");
        } else {
          printf("Todos were successfully saved to the todos.txt file\n");
        }
      }

      break;
    } while (true);

    print_todos(todos, c_todos);
  } while (true);

  print_todos(todos, c_todos);

  return EXIT_SUCCESS;
}
