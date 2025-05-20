#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[5];

    for (int i = 0; i <= 4; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    for (int i = 4; i >= 0; i--) {
        printf("%d\n", array[i]);
    }

    return EXIT_SUCCESS;
}
