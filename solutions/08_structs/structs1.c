// structs1.c - solution

#include <stdio.h>

struct person {
    const char *name;
    int age;
};

int main(void)
{
    struct person p;

    p.name = "Ada";
    p.age = 36;
    printf("%s is %d years old\n", p.name, p.age);

    struct person q = {.name = "Grace", .age = 45};
    printf("%s is %d years old\n", q.name, q.age);
    return 0;
}
