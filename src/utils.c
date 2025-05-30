#include <stddef.h>
#include <stdlib.h>

#include "utils.h"

u_string *u_strdup(const char *s)
{
  if (s == NULL)
  {
    return NULL;
  }
  size_t len = 0;
  while (s[len] != '\0')
  {
    len++;
  }
  u_string *dup = malloc(len + 1);
  if (dup == NULL)
  {
    return NULL;
  }
  for (size_t i = 0; i < len; i++)
  {
    dup[i] = s[i];
  }
  dup[len] = '\0';
  return dup;
}

void u_strdup_free(u_string *s)
{
  if (!s || s == NULL)
  {
    return;
  }
  free(s);
  s = NULL;
}
