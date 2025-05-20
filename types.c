#include <stdio.h>
#include <stdlib.h>

int main() {
    int int_number = 42;
    char char_symbol = 'W';
    float float_number = 3.14;
    double double_number = 2.71828;

    printf("Int: %d\n", int_number);
    printf("Char: %c\n", char_symbol);
    printf("Float: %.2f\n", float_number);
    printf("Double: %.5f\n", double_number);

    return EXIT_SUCCESS;
}
