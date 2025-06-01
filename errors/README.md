# Leasoso Error Handling Project

A lightweight error handling implementation for C applications that provides a structured way to manage and report errors.

## Overview

This project implements a simple error handling mechanism in C with error codes and messages. It defines an `Error` structure and an `ErrorCode` enum to standardize error reporting across your C applications.

## Features

- Predefined error codes for common error scenarios
- Error structure that holds both error code and descriptive message
- Convenient macro for reporting errors
- Simple error printing functionality

## Usage

### Basic Usage

```c
#include "errors.h"

int main(void) {
  // Create an error variable
  Error err = { .code = ERR_NONE, .msg = "No error" };

  // If an error occurs in your code, set the error
  if (some_condition_failed) {
    ERROR_REPO(&err, ERR_INVALID_INPUT, "The input was invalid");
  }

  // Print the error
  print_error(&err);

  return err.code;
}
```

### Error Codes

The project provides the following predefined error codes:

| Code                  | Value | Description              |
| --------------------- | ----- | ------------------------ |
| ERR_NONE              | 0     | No error                 |
| ERR_INVALID_INPUT     | 1     | Invalid input provided   |
| ERR_OUT_OF_MEMORY     | 2     | Memory allocation failed |
| ERR_FILE_NOT_FOUND    | 3     | File not found           |
| ERR_PERMISSION_DENIED | 4     | Permission denied        |
| ERR_TIMEOUT           | 5     | Operation timed out      |
| ERR_UNKNOWN           | 6     | Unknown error            |

## Example

```c
#include "errors.h"
#include <stdlib.h>

Error* allocate_memory(size_t size) {
  static Error err = { .code = ERR_NONE, .msg = "Memory allocated successfully" };

  void* ptr = malloc(size);
  if (!ptr) {
    ERROR_REPO(&err, ERR_OUT_OF_MEMORY, "Failed to allocate memory");
    return &err;
  }

  // Use the memory...

  return &err;
}
```

## Building

To use this error handling implementation, simply include both `errors.h` and `errors.c` in your project.
