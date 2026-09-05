// fnptr2.c
//
// CONCEPT
// `qsort` from <stdlib.h> sorts any array, because you tell it how to
// compare two elements:
//
//     void qsort(void *base, size_t count, size_t size,
//                int (*compare)(const void *, const void *));
//
// It knows nothing about the element type; it only moves `size`-byte
// blocks around and asks your comparator which of two blocks comes
// first. The comparator receives `const void *` pointers *to the
// elements*, casts them back to the real type, and returns negative,
// zero or positive (like strcmp).
//
//     static int by_int(const void *a, const void *b)
//     {
//         int x = *(const int *)a;
//         int y = *(const int *)b;
//         return (x > y) - (x < y);      // not x - y: that can overflow
//     }
//
// For an array of strings (`const char *names[]`), the elements are
// pointers, so the comparator gets pointers to pointers:
// `*(const char *const *)a`. Also in <stdlib.h>: `bsearch`, binary
// search with the same comparator.
//
// WHEN YOU USE THIS
// Every time you sort in C. Writing a comparator per ordering ("by
// name", "by size descending, then name") is the C way of expressing
// sort keys.
//
// TASK
// Write three comparators and use them with qsort: ints ascending,
// strings by length (shortest first, ties alphabetically), and
// `struct employee` by salary descending.
//
// EXPECTED OUTPUT
//     ints: -3 1 4 9 15
//     names: Bo Ada Zed Carl Grace
//     employees: Grace 95000, Ada 90000, Bo 70000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee {
    const char *name;
    int salary;
};

static int by_int(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

static int by_length_then_alpha(const void *a, const void *b)
{
    // TODO: a and b point to `const char *` elements.
    (void)a;
    (void)b;
    return 0;
}

static int by_salary_desc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
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
