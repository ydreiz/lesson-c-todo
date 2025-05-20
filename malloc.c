#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Size array must be oabove zero!\n");
        return EXIT_FAILURE;
    }

    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    printf("Sum of array elements: %d\n", sum);

    free(arr);

    return EXIT_SUCCESS;
}
