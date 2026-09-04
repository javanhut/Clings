// structs3.c
//
// Arrays of structs are a common way to hold a list of records. Replace
// `???` to print each item and add up the stock. Expected output:
//
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
