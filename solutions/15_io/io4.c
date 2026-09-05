// io4.c - solution

#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[128];
    char name[16];
    int age;

    while (fgets(line, sizeof line, stdin) != NULL) {
        if (sscanf(line, "%15s %d", name, &age) == 2) {
            printf("%s is %d\n", name, age);
        } else {
            line[strcspn(line, "\n")] = '\0';
            printf("bad line: %s\n", line);
        }
    }
    return 0;
}
