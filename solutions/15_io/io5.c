// io5.c - solution

#include <stdio.h>
#include <stdlib.h>

#define PATH "io5_numbers.tmp"

int write_numbers(const char *path, int count)
{
    FILE *f = fopen(path, "w");

    if (f == NULL) {
        return -1;
    }
    for (int i = 1; i <= count; i++) {
        fprintf(f, "%d\n", i);
    }
    fclose(f);
    return count;
}

long sum_file(const char *path)
{
    FILE *f = fopen(path, "r");
    char line[64];
    long sum = 0;

    if (f == NULL) {
        return -1;
    }
    while (fgets(line, sizeof line, f) != NULL) {
        sum += strtol(line, NULL, 10);
    }
    fclose(f);
    return sum;
}

int main(void)
{
    int written = write_numbers(PATH, 10);
    if (written < 0) {
        fprintf(stderr, "cannot write %s\n", PATH);
        return 1;
    }
    printf("wrote %d numbers\n", written);
    printf("sum: %ld\n", sum_file(PATH));
    remove(PATH);
    printf("after remove: %ld\n", sum_file(PATH));
    return 0;
}
