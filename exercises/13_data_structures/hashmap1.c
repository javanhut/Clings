// hashmap1.c
//
// CONCEPT
// A *hash map* gives O(1) average lookup by key. A hash function turns
// the key (here a string) into a number; `hash % bucket_count` picks a
// bucket; each bucket is a linked list of entries whose keys landed
// there ("separate chaining"). Lookup hashes the key, walks that one
// short list comparing keys with strcmp.
//
// A simple, decent string hash is djb2:
//     unsigned long h = 5381;
//     for each byte c: h = h * 33 + c;
// Real code uses better ones (FNV-1a, SipHash) and grows the table when
// the average chain gets long, but the structure is the same.
//
// Ownership: the map copies each key (the caller's string may go away)
// and frees all of them in map_free. Pointer-to-pointer (list2) makes
// remove clean.
//
// WHEN YOU USE THIS
// Symbol tables, caches, counting occurrences, deduplication,
// configuration lookup: whenever "find by name" must be fast. C has no
// built-in map, so every project has one of these.
//
// TASK
// Write hash_string (djb2), map_put (insert or update; copies the key),
// map_get (returns a pointer to the value or NULL), map_remove and
// map_free.
//
// EXPECTED OUTPUT
//     apple -> 3
//     pear -> 5
//     plum -> (none)
//     apple -> 4
//     removed pear: yes
//     removed pear: no
//     pear -> (none)
//     count: 1

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
    // TODO: djb2
    (void)s;
    return 0;
}

bool map_put(struct map *m, const char *key, int value)
{
    // TODO
    (void)m;
    (void)key;
    (void)value;
    return false;
}

int *map_get(struct map *m, const char *key)
{
    // TODO
    (void)m;
    (void)key;
    return NULL;
}

bool map_remove(struct map *m, const char *key)
{
    // TODO
    (void)m;
    (void)key;
    return false;
}

void map_free(struct map *m)
{
    // TODO
    (void)m;
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
