#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

int main(void)
{
    Person person;

    printf("Enter name: ");
    fgets(person.name, sizeof(person.name), stdin);
    person.name[strcspn(person.name, "\n")] = 0;

    printf("Enter age: ");
    if (scanf("%d", &person.age) != 1) {
        printf("Invalid input for age.\n");
        return EXIT_FAILURE;
    }

    printf("Name: %s Age: %d\n", person.name, person.age);

    return EXIT_SUCCESS;
}

