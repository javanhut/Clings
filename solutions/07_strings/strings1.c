// strings1.c - solution

#include <stdio.h>
#include <string.h>

int main(void)
{
    char greeting[] = "hello";

    printf("%s has %zu characters\n", greeting, strlen(greeting));
    printf("the array takes %zu bytes\n", sizeof(greeting));
    return 0;
}
