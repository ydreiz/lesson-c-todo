#include "person.h"

void birthday_all(Person persons[], int n)
{
    for (int i = 0; i < n; i++) {
        persons[i].age = persons[i].age + 1;
    }
}
