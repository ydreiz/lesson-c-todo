#include <stdio.h>
#include <stdlib.h>

// This program demonstrates dynamic memory allocation using malloc and realloc.
// It allocates an array of integers, initializes it, and then reallocates it to
// a larger size.
// It also prints the addresses of the pointer and its elements before and after
// reallocation.

int main(void) {
  // Allocate memory for an array of integers
  int *arr = malloc(5 * sizeof(int));
  if (!arr) {
    perror("Memore allocation failed");
    return 1;
  }
  for (int i = 0; i < 5; i++) {
    arr[i] = i * 10;
  }
  // Show address and value of each element
  for (int i = 0; i < 5; i++) {
    printf("arr[%d] = %d at %p\n", i, arr[i], (void *)&arr[i]);
  }
  printf("\nAddress of the pointer and the first element:\n");
  printf("arr (pointer value): %p\n", (void *)arr);
  printf("&arr (address of pointer): %p\n", (void *)&arr);
  printf("&arr[0] (address of first element): %p\n", (void *)&arr[0]);
  // Reallocate memory for the array
  int *tmp_arr = realloc(arr, 10 * sizeof(int));
  if (!tmp_arr) {
    perror("Memory reallocation failed");
    free(arr);
    return 1;
  }
  arr = tmp_arr;
  printf("\nAfter reallocation\n");
  // Show address and value of each element after reallocation
  for (int i = 0; i < 10; i++) {
    arr[i] = i * 10;
  }
  for (int i = 0; i < 10; i++) {
    printf("arr[%d] = %d at %p\n", i, arr[i], (void *)&arr[i]);
  }
  printf("\nAddress of the pointer and the first element:\n");
  printf("arr (pointer value): %p\n", (void *)arr);
  printf("&arr (address of pointer): %p\n", (void *)&arr);
  printf("&arr[0] (address of first element): %p\n", (void *)&arr[0]);
  free(arr);
  return 0;
}
