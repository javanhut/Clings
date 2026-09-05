// strings2.c - solution

#include <stdio.h>
#include <string.h>

int main(void)
{
    char answer[] = "yes";

    if (strcmp(answer, "yes") == 0) {
        printf("Confirmed\n");
    } else {
        printf("Denied\n");
    }
    if (strcmp("apple", "banana") < 0) {
        printf("\"apple\" sorts before \"banana\"\n");
    }
    return 0;
}
