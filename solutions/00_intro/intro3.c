// intro3.c - solution

#include <stdio.h>

int main(void)
{
    const char *name = "Ada";
    int age = 36;
    double height = 1.7;
    char initial = 'A';

    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("Height: %.2f m\n", height);
    printf("Initial: %c\n", initial);
    printf("Progress: 100%%\n");
    return 0;
}
