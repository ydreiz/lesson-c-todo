#ifndef ERRORS_H
#define ERRORS_H

#include <stdbool.h>

typedef enum
{
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
} LogLevel;

void log_message(LogLevel level, const char *format, ...);
void p_error(const char *msg);
void p_warn(const char *msg);
void p_info(const char *msg);

void enable_logging(bool enable);
bool is_logging_enabled(void);

#endif // !ERRORS_H
