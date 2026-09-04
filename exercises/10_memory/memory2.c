// memory2.c
//
// `realloc` resizes a block of memory, keeping its contents. A growable
// array doubles its capacity whenever it runs out of room.
//
// Complete `push` so that it grows the array when `len == capacity`.
// Expected output:
//
//     Stored 10 numbers, capacity grew to 16
//     Last number: 90

#include <stdio.h>
#include <stdlib.h>

struct vec {
    int *data;
    size_t len;
    size_t capacity;
};

int push(struct vec *v, int value)
{
    if (v->len == v->capacity) {
        size_t new_capacity = ???;
        int *new_data = realloc(v->data, ???);
        if (new_data == NULL) {
            return 0;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }
    v->data[v->len] = value;
    v->len++;
    return 1;
}

int main(void)
{
    struct vec v = {NULL, 0, 0};

    for (int i = 0; i < 10; i++) {
        if (!push(&v, i * 10)) {
            return 1;
        }
    }

    printf("Stored %zu numbers, capacity grew to %zu\n", v.len, v.capacity);
    printf("Last number: %d\n", v.data[v.len - 1]);

    free(v.data);
    return 0;
}
