#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "todo.h"
#include "utils.h"

void fill_stub_todos(TodoList *todos, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    u_string title[20];
    sprintf(title, "TEST %lu", todos->next_id);
    todo_add(title, (i % 2 ? true : false), todos);
  }
}

void capture_stderr(void (*func)(const char *msg), const char *msg, char *out_buf, size_t buf_size)
{
  FILE *old_stderr = stderr;
  FILE *tmp = tmpfile();
  assert(tmp != NULL);

  stderr = tmp;
  func(msg);
  fflush(tmp);

  rewind(tmp);
  size_t n = fread(out_buf, 1, buf_size - 1, tmp);
  out_buf[n] = '\0';

  fclose(tmp);
  stderr = old_stderr;
}

void capture_stdout(void (*func)(const TodoList *), const TodoList *todos, char *out_buf, size_t buf_size)
{
  FILE *old_stdout = stdout;
  FILE *tmp = tmpfile();
  assert(tmp != NULL);

  stdout = tmp;
  func(todos);
  fflush(tmp);

  rewind(tmp);
  size_t n = fread(out_buf, 1, buf_size - 1, tmp);
  out_buf[n] = '\0';

  fclose(tmp);
  stdout = old_stdout;
}

FILE *create_tmpfile_with_content(const char *content)
{
  FILE *tmp = tmpfile();
  if (!tmp)
  {
    perror("tmpfile");
    return NULL;
  }

  if (content)
  {
    fputs(content, tmp);
    fflush(tmp);
    rewind(tmp);
  }

  return tmp;
}
