// structs6.c
//
// CONCEPT
// Struct members can be structs and arrays. A rectangle is two points; an
// inventory is an array of items plus a count of how many slots are used.
// Access chains: `r.max.x`, `inv.items[i].stock`, `inv->items[i].name`.
//
// A struct that holds a fixed-size array *and a count* is the standard
// way to have a small, bounded list without dynamic memory:
//
//     struct inventory {
//         struct item items[MAX_ITEMS];
//         size_t count;               // how many of items[] are in use
//     };
//
// Adding checks `count < MAX_ITEMS` first; removing shifts the tail down
// (or, when order does not matter, moves the last element into the hole,
// the "swap-remove" trick, which is O(1)).
//
// WHEN YOU USE THIS
// Geometry (rect contains / intersects), fixed-capacity queues and
// stacks in embedded code, any nested record: an address inside a
// customer inside an order.
//
// TASK
// Write `rect_area`, `rect_contains` (edges count as inside),
// `inventory_add` (returns false when full) and `inventory_remove`
// (removes the item with that name using swap-remove; returns false if
// it is not there).
//
// EXPECTED OUTPUT
//     area: 12
//     (3, 3) inside: yes
//     (6, 1) inside: no
//     added apple, pear, plum
//     inventory full
//     removed pear
//     no such item: kiwi
//     apple: 10
//     plum: 20

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
    // TODO
    (void)r;
    return 0;
}

bool rect_contains(struct rect r, struct point p)
{
    // TODO
    (void)r;
    (void)p;
    return false;
}

bool inventory_add(struct inventory *inv, const char *name, int stock)
{
    // TODO
    (void)inv;
    (void)name;
    (void)stock;
    return false;
}

bool inventory_remove(struct inventory *inv, const char *name)
{
    // TODO: swap-remove.
    (void)inv;
    (void)name;
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
