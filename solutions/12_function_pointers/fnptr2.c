// fnptr2.c - solution

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee {
    const char *name;
    int salary;
};

static int by_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    return (x > y) - (x < y);
}

static int by_length_then_alpha(const void *a, const void *b)
{
    const char *x = *(const char *const *)a;
    const char *y = *(const char *const *)b;
    size_t lx = strlen(x);
    size_t ly = strlen(y);

    if (lx != ly) {
        return lx < ly ? -1 : 1;
    }
    return strcmp(x, y);
}

static int by_salary_desc(const void *a, const void *b)
{
    const struct employee *x = a;
    const struct employee *y = b;

    return (y->salary > x->salary) - (y->salary < x->salary);
}

int main(void)
{
    int ints[] = {9, -3, 15, 1, 4};
    const char *names[] = {"Grace", "Ada", "Zed", "Carl", "Bo"};
    struct employee staff[] = {
        {"Ada", 90000},
        {"Bo", 70000},
        {"Grace", 95000},
    };

    qsort(ints, 5, sizeof ints[0], by_int);
    qsort(names, 5, sizeof names[0], by_length_then_alpha);
    qsort(staff, 3, sizeof staff[0], by_salary_desc);

    printf("ints:");
    for (int i = 0; i < 5; i++) {
        printf(" %d", ints[i]);
    }
    printf("\nnames:");
    for (int i = 0; i < 5; i++) {
        printf(" %s", names[i]);
    }
    printf("\nemployees: ");
    for (int i = 0; i < 3; i++) {
        printf("%s%s %d", i > 0 ? ", " : "", staff[i].name, staff[i].salary);
    }
    printf("\n");
    return 0;
}
