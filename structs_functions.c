#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

#define MAX_PERSONS 100

int main(void)
{
    int n;
    printf("Enter number of persons (<=%d): ", MAX_PERSONS);
    scanf("%d", &n);

    if (n > MAX_PERSONS) {
        printf("Input persons is above %d\n", MAX_PERSONS);
        return EXIT_FAILURE;
    }

    getchar();

    Person persons[n];
    for (int i = 0; i < n; i++) {
        printf("[%d] Enter name: ", i + 1);
        fgets(persons[i].name, sizeof(persons[i].name), stdin);
        persons[i].name[strcspn(persons[i].name, "\n")] = 0;

        printf("[%d] Enter age: ", i + 1);
        scanf("%d", &persons[i].age);
        getchar();
    }

    printf("List person:\n");

    birthday_all(persons, n);

    for (int i = 0; i < n; i++) {
        printf("Name: %s, Age: %d\n", persons[i].name, persons[i].age);
    }

    return EXIT_SUCCESS;
}

