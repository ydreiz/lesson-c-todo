#include "errors.h"
#include <stdio.h>

static Error ok = (Error){.code = ERR_NONE, .msg = "No error"};

void print_error(Error *err) {
  if (err->code != ERR_NONE) {
    printf("Error code: %d, Message: %s\n", err->code, err->msg);
  } else {
    printf("%s\n", err->msg);
  }
}

static Error *some_precess() {
  Error *err = &ok;
  // Simulate an error
  return err;
}

int main(void) {
  Error *err = &ok;

  err = some_precess();

  print_error(err);

  if (err->code == ERR_NONE) {
    ERROR_REPO(err, ERR_PERMISSION_DENIED, "Permission denied");
  }

  print_error(err);

  return 0;
}
