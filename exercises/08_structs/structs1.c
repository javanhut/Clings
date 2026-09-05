// structs1.c
//
// CONCEPT
// A `struct` bundles several values of different types into one thing
// with named *members*. Defining a struct creates a new type; it does
// not create a variable:
//
//     struct person {          // the type is named "struct person"
//         const char *name;
//         int age;
//     };
//     struct person p;         // a variable of that type
//     p.age = 36;              // members are accessed with `.`
//
// Initialize all at once with braces, in member order, or by name with
// *designated initializers* (C99), which are clearer and survive
// reordering of the members:
//
//     struct person p = {"Ada", 36};
//     struct person q = {.name = "Ada", .age = 36};
//
// WHEN YOU USE THIS
// Structs are how C models anything with more than one property: a
// point, a file handle, a network packet, a configuration. Every
// non-trivial C program is mostly structs and the functions that operate
// on them, which is what "object-oriented C" means in practice.
//
// TASK
// Define the members of `struct person` so main compiles, and
// initialize `q` with a designated initializer.
//
// EXPECTED OUTPUT
//     Ada is 36 years old
//     Grace is 45 years old

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

    struct person q = ???;
    printf("%s is %d years old\n", q.name, q.age);
    return 0;
}
