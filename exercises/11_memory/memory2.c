// memory2.c
//
// CONCEPT
// `realloc(p, new_size)` resizes a heap block, keeping its contents. It
// may move the block to a new address, in which case the old pointer is
// invalid afterwards. It returns NULL (and leaves the old block intact)
// when it fails. Hence the idiom:
//
//     int *bigger = realloc(v->data, new_cap * sizeof *bigger);
//     if (bigger == NULL) { return false; }   // v->data is still valid
//     v->data = bigger;
//
// Assigning `v->data = realloc(v->data, ...)` directly loses the only
// pointer to the old block on failure: a leak and a dangling structure.
//
// A *growable array* ("vector", "dynamic array") keeps a length and a
// capacity, and doubles the capacity when full. Doubling makes the
// average cost of an append constant, because reallocations become rare
// as the array grows.
//
// WHEN YOU USE THIS
// Everywhere a list of unknown length is collected: lines of a file,
// tokens, results. This struct is the most-written data structure in C.
//
// TASK
// Complete `push` so it grows the array when `len == capacity` (start
// with capacity 4 when it is 0, then double), and `vec_free`.
//
// EXPECTED OUTPUT
//     Stored 10 numbers, capacity grew to 16
//     Last number: 90

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct vec {
    int *data;
    size_t len;
    size_t capacity;
};

bool push(struct vec *v, int value)
{
    // TODO: grow if needed, then store value.
    (void)v;
    (void)value;
    return false;
}

void vec_free(struct vec *v)
{
    // TODO: free the data and reset the fields.
    (void)v;
}

int main(void)
{
    struct vec v = {NULL, 0, 0};

    for (int i = 0; i < 10; i++) {
        if (!push(&v, i * 10)) {
            printf("out of memory\n");
            return 1;
        }
    }
    printf("Stored %zu numbers, capacity grew to %zu\n", v.len, v.capacity);
    printf("Last number: %d\n", v.data[v.len - 1]);
    vec_free(&v);
    return 0;
}
