#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if (n == 0) {
        printf("Zero\n");
        return EXIT_SUCCESS;
    }

    if (n > 0) {
        printf("Positive\n");
        for (int i = 1; i <= n; i++) {
            printf("%d\n", i);
        }
        return EXIT_SUCCESS;
    }


    if (n < 0) {
        printf("Negative\n");
        for (int i = n; i <= -1; i++) {
            printf("%d\n", i);
        }
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
