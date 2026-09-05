// memory2.c - solution

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
    if (v->len == v->capacity) {
        size_t new_cap = v->capacity == 0 ? 4 : v->capacity * 2;
        int *bigger = realloc(v->data, new_cap * sizeof *bigger);
        if (bigger == NULL) {
            return false;
        }
        v->data = bigger;
        v->capacity = new_cap;
    }
    v->data[v->len++] = value;
    return true;
}

void vec_free(struct vec *v)
{
    free(v->data);
    v->data = NULL;
    v->len = 0;
    v->capacity = 0;
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
