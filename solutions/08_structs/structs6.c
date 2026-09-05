// structs6.c - solution

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 3

struct point {
    int x;
    int y;
};

struct rect {
    struct point min;
    struct point max;
};

struct item {
    const char *name;
    int stock;
};

struct inventory {
    struct item items[MAX_ITEMS];
    size_t count;
};

int rect_area(struct rect r)
{
    return (r.max.x - r.min.x) * (r.max.y - r.min.y);
}

bool rect_contains(struct rect r, struct point p)
{
    return p.x >= r.min.x && p.x <= r.max.x && p.y >= r.min.y && p.y <= r.max.y;
}

bool inventory_add(struct inventory *inv, const char *name, int stock)
{
    if (inv->count >= MAX_ITEMS) {
        return false;
    }
    inv->items[inv->count].name = name;
    inv->items[inv->count].stock = stock;
    inv->count++;
    return true;
}

bool inventory_remove(struct inventory *inv, const char *name)
{
    for (size_t i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {
            inv->items[i] = inv->items[inv->count - 1];
            inv->count--;
            return true;
        }
    }
    return false;
}

int main(void)
{
    struct rect r = {{1, 1}, {5, 4}};
    struct inventory inv = {.count = 0};

    printf("area: %d\n", rect_area(r));
    printf("(3, 3) inside: %s\n", rect_contains(r, (struct point){3, 3}) ? "yes" : "no");
    printf("(6, 1) inside: %s\n", rect_contains(r, (struct point){6, 1}) ? "yes" : "no");

    if (inventory_add(&inv, "apple", 10) && inventory_add(&inv, "pear", 12) &&
        inventory_add(&inv, "plum", 20)) {
        printf("added apple, pear, plum\n");
    }
    if (!inventory_add(&inv, "kiwi", 1)) {
        printf("inventory full\n");
    }
    if (inventory_remove(&inv, "pear")) {
        printf("removed pear\n");
    }
    if (!inventory_remove(&inv, "kiwi")) {
        printf("no such item: kiwi\n");
    }
    for (size_t i = 0; i < inv.count; i++) {
        printf("%s: %d\n", inv.items[i].name, inv.items[i].stock);
    }
    return 0;
}
