// structs1.c
//
// A struct groups several values into one. Each value is a *member* with
// its own name and type. Define the members of `struct person` so that the
// code in main compiles and prints:
//
//     Ada is 36 years old

#include <stdio.h>

struct person {
    // TODO: add the members `name` and `age`.
};

int main(void)
{
    struct person p;

    p.name = "Ada";
    p.age = 36;

    printf("%s is %d years old\n", p.name, p.age);
    return 0;
}
