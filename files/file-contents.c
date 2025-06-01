#include <stdio.h>
#include <stdlib.h>

long file_size(FILE *file) {
  if (!file) {
    return -1;
  }
  if (fseek(file, 0, SEEK_END) != 0) {
    fprintf(stderr, "Error seeking to end of file\n");
    return -1;
  }
  long size = ftell(file);
  if (size < 0) {
    fprintf(stderr, "Error getting file size\n");
    return -1;
  }
  rewind(file);
  return size;
}

char *file_contents(const char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "Can't open files %s\n", path);
    return NULL;
  }
  fprintf(stderr, "File opened successfully: %s\n", path);
  long size = file_size(file);
  if (size <= 0) {
    fclose(file);
    fprintf(stderr, "File is empty or size is invalid.\n");
    return NULL;
  } else if (size > 100 * 1024 * 1024) {
    fprintf(stderr, "File size exceeds 100 MB limit: %ld bytes\n", size);
    fclose(file);
    return NULL;
  }
  printf("File size: %ld bytes\n", size);
  char *contents = malloc(size + 1);
  if (!contents) {
    fprintf(stderr, "Memmory allocation failed\n");
    fclose(file);
    return NULL;
  }
  size_t read_size = fread(contents, 1, size, file);
  fclose(file);
  if (read_size != size) {
    fprintf(stderr, "Error reading file: expected %ld bytes, got %zu bytes\n",
            size, read_size);
    free(contents);
    return NULL;
  }
  contents[read_size] = '\0';
  return contents;
}

void file_contents_free(char *contents) {
  if (contents) {
    free(contents);
    contents = NULL;
  } else {
    fprintf(stderr, "Attempted to free NULL pointer\n");
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  char *contents = file_contents(argv[1]);

  printf("File contents:\n----\n%s----\n", contents ? contents : "NULL");

  file_contents_free(contents);

  return 0;
}
