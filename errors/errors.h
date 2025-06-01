#ifndef ERRORS_H
#define ERRORS_H

typedef enum ErrorCode {
  ERR_NONE = 0,          // No error
  ERR_INVALID_INPUT,     // Invalid input provided
  ERR_OUT_OF_MEMORY,     // Memory allocation failed
  ERR_FILE_NOT_FOUND,    // File not found
  ERR_PERMISSION_DENIED, // Permission denied
  ERR_TIMEOUT,           // Operation timed out
  ERR_UNKNOWN            // Unknown error
} ErrorCode;

typedef struct Error {
  ErrorCode code;  // Error code
  const char *msg; // Error message
} Error;

#define ERROR_REPO(err, c, m)                                                  \
  do {                                                                         \
    (err)->code = (c);                                                         \
    (err)->msg = (m);                                                          \
  } while (0);

#endif // !ERRORS_H
