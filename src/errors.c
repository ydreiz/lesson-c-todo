#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include "errors.h"

static int logging_enabled = true;

void enable_logging(bool enable) { logging_enabled = enable; }

bool is_logging_enabled() { return logging_enabled; }

void log_message(LogLevel level, const char *format, ...)
{
  if (!logging_enabled)
  {
    return;
  }

  const char *level_str = "";
  switch (level)
  {
  case LOG_LEVEL_INFO:
    level_str = "[INFO] ";
    break;
  case LOG_LEVEL_WARN:
    level_str = "[WARN] ";
    break;
  case LOG_LEVEL_ERROR:
    level_str = "[ERROR] ";
    break;
  }

  va_list args;
  va_start(args, format);
  fprintf(stderr, "%s", level_str);
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n");
  va_end(args);
}

void p_error(const char *msg) { log_message(LOG_LEVEL_ERROR, "%s", msg); }

void p_warn(const char *msg) { log_message(LOG_LEVEL_WARN, "%s", msg); }

void p_info(const char *msg) { log_message(LOG_LEVEL_INFO, "%s", msg); }
