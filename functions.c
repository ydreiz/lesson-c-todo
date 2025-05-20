#include <stdio.h>
#include <stdlib.h>

int abs_value(int n)
{
    if (n < 0) {
        return -n;
    }
    return n;
}

int main(void)
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    printf("Absolute value %d\n", abs_value(n));

    return EXIT_SUCCESS;
}
