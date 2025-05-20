#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = 0;

    printf("The '%s' is length: %zu\n", str, strlen(str));

    if (strcmp("C language", str) == 0) {
        printf("Matched!\n");
    } else {
        printf("Not matched!\n");
    }

    return EXIT_SUCCESS;
}
