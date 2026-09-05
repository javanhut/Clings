// structs3.c - solution

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
        printf("%s: %d\n", items[i].name, items[i].stock);
        total += items[i].stock;
    }

    printf("Total: %d\n", total);
    return 0;
}
