// hashmap1.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS 16

struct entry {
    char *key;
    int value;
    struct entry *next;
};

struct map {
    struct entry *buckets[BUCKETS];
    size_t count;
};

unsigned long hash_string(const char *s)
{
    unsigned long h = 5381;

    for (; *s != '\0'; s++) {
        h = h * 33 + (unsigned char)*s;
    }
    return h;
}

static struct entry **find_slot(struct map *m, const char *key)
{
    struct entry **pp = &m->buckets[hash_string(key) % BUCKETS];

    while (*pp != NULL && strcmp((*pp)->key, key) != 0) {
        pp = &(*pp)->next;
    }
    return pp;
}

bool map_put(struct map *m, const char *key, int value)
{
    struct entry **pp = find_slot(m, key);

    if (*pp != NULL) {
        (*pp)->value = value;
        return true;
    }
    struct entry *e = malloc(sizeof *e);
    if (e == NULL) {
        return false;
    }
    size_t len = strlen(key) + 1;
    e->key = malloc(len);
    if (e->key == NULL) {
        free(e);
        return false;
    }
    memcpy(e->key, key, len);
    e->value = value;
    e->next = NULL;
    *pp = e;
    m->count++;
    return true;
}

int *map_get(struct map *m, const char *key)
{
    struct entry *e = *find_slot(m, key);

    return e != NULL ? &e->value : NULL;
}

bool map_remove(struct map *m, const char *key)
{
    struct entry **pp = find_slot(m, key);

    if (*pp == NULL) {
        return false;
    }
    struct entry *doomed = *pp;
    *pp = doomed->next;
    free(doomed->key);
    free(doomed);
    m->count--;
    return true;
}

void map_free(struct map *m)
{
    for (size_t b = 0; b < BUCKETS; b++) {
        struct entry *e = m->buckets[b];
        while (e != NULL) {
            struct entry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
        m->buckets[b] = NULL;
    }
    m->count = 0;
}

static void show(struct map *m, const char *key)
{
    int *v = map_get(m, key);
    if (v != NULL) {
        printf("%s -> %d\n", key, *v);
    } else {
        printf("%s -> (none)\n", key);
    }
}

int main(void)
{
    struct map m = {{NULL}, 0};
    char key[8] = "apple";

    map_put(&m, key, 3);
    strcpy(key, "pear");
    map_put(&m, key, 5);
    show(&m, "apple");
    show(&m, "pear");
    show(&m, "plum");
    map_put(&m, "apple", 4);
    show(&m, "apple");
    printf("removed pear: %s\n", map_remove(&m, "pear") ? "yes" : "no");
    printf("removed pear: %s\n", map_remove(&m, "pear") ? "yes" : "no");
    show(&m, "pear");
    printf("count: %zu\n", m.count);
    map_free(&m);
    return 0;
}
