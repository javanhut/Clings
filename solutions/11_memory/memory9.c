// memory9.c - solution

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
    int x;
    int y;
};

int main(void)
{
    const char *text = "sanitizers are great";
    char *copy = malloc(strlen(text) + 1);
    if (copy == NULL) {
        return 1;
    }
    strcpy(copy, text);
    printf("copy: %s\n", copy);
    free(copy);

    struct point *pt = malloc(sizeof *pt);
    if (pt == NULL) {
        return 1;
    }
    pt->x = 3;
    pt->y = 4;
    printf("point: (%d, %d)\n", pt->x, pt->y);
    free(pt);

    int n = 10;
    int *values = malloc(n * sizeof *values);
    if (values == NULL) {
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        values[i] = i;
        sum += values[i];
    }
    printf("sum: %d\n", sum);
    free(values);
    return 0;
}
