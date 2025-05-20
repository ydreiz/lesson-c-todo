#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *pn = &n;

    printf("Enter a number: ");
    scanf("%d", pn);

    *pn = *pn + 10;

    printf("The number: %d\n", n);

    return EXIT_SUCCESS;
}
