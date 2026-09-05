// io1.c - solution

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("%d arguments\n", argc - 1);
    for (int i = 1; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);
    }

    int first = 1;
    if (argc > 1 && strcmp(argv[1], "-v") == 0) {
        printf("verbose: on\n");
        first = 2;
    } else {
        printf("verbose: off\n");
    }
    for (int i = first; i < argc; i++) {
        printf("positional: %s\n", argv[i]);
    }
    return 0;
}
