#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  void *h_add;
  int (*add)(int, int);
  char *(*version)(void);
  h_add = dlopen("./libadd.so", RTLD_LAZY);
  if (!h_add) {
    fprintf(stderr, "Can'n library: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  add = dlsym(h_add, "add");
  char *error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "Not found add: %s\n", error);
    dlclose(h_add);
    exit(EXIT_FAILURE);
  }
  version = dlsym(h_add, "add_version");
  printf("add_version = %s\n", version());

  printf("add(12, 22) = %d\n", add(12, 22));

  dlclose(h_add);
  return EXIT_SUCCESS;
}
