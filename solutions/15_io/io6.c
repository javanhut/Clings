// io6.c - solution

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(const char *path, long *out)
{
    FILE *f = fopen(path, "r");
    char line[256];
    long n = 0;

    if (f == NULL) {
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
        return -1;
    }
    while (fgets(line, sizeof line, f) != NULL) {
        if (strchr(line, '\n') != NULL) {
            n++;
        }
    }
    fclose(f);
    *out = n;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s FILE\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("counting lines in %s\n", argv[1]);
    long n;
    if (count_lines(argv[1], &n) != 0) {
        return EXIT_FAILURE;
    }
    printf("%ld lines\n", n);
    return EXIT_SUCCESS;
}
