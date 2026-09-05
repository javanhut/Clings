// structs3.c
//
// CONCEPT
// An array of structs is the simplest "table" in C: each element is one
// record, and `items[i].stock` reaches into record i. Initialize with
// nested braces, one inner pair per element. As with any array, the
// element count comes from sizeof(items) / sizeof(items[0]).
//
// Because the records are stored contiguously, a loop over them walks
// memory in order, which is fast. This layout ("array of structs") is the
// default; the alternative, one array per member ("struct of arrays"),
// is a performance technique for very hot loops.
//
// WHEN YOU USE THIS
// Lookup tables of commands, options, test cases, unit conversions;
// anything you would write as a list of tuples elsewhere.
//
// TASK
// Replace the `???` to print each item and add up the stock.
//
// EXPECTED OUTPUT
//     apple: 10
//     pear: 12
//     plum: 20
//     Total: 42

#include <stdio.h>

struct item {
    const char *name;
    int stock;
};

int main(void)
{
    struct item items[] = {
        {"apple", 10},
        {"pear", 12},
        {"plum", 20},
    };
    size_t count = sizeof(items) / sizeof(items[0]);
    int total = 0;

    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", ???, ???);
        total += ???;
    }

    printf("Total: %d\n", total);
    return 0;
}
