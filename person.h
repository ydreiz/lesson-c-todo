#ifndef H_PERSON
#define H_PERSON

#define NAME_LENGTH 50

typedef struct{
    char name[NAME_LENGTH];
    int age;
} Person;

void birthday_all(Person persons[], int n);

#endif // !H_PERSON
