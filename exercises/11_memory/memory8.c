// memory8.c
//
// CONCEPT
// A struct that holds a pointer to heap memory *owns* that memory (or
// borrows it; you must decide which, and say so). The C convention for
// an owning struct is a pair of functions:
//
//     struct person *person_create(const char *name, int age);
//     void person_destroy(struct person *p);
//
// create allocates the struct *and* copies whatever it needs to own (the
// name, here: the caller's string might change or die). destroy frees
// the owned members first, then the struct. If create fails halfway, it
// must undo what it already did before returning NULL.
//
// The trap is copying the struct: `struct person b = *a;` copies the
// pointer, not the name. Now two structs think they own one string, and
// destroying both is a double free. Either forbid copies (pass around
// pointers only) or write a `_clone` that deep-copies.
//
// WHEN YOU USE THIS
// This is how every C library exposes an object: `foo_new`/`foo_free`,
// `xxx_init`/`xxx_destroy`, `SDL_CreateWindow`/`SDL_DestroyWindow`. When
// you see such a pair, the rule is: every create is matched by exactly
// one destroy, and nothing touches the object after destroy.
//
// TASK
// Write person_create, person_rename (replaces the owned name with a copy
// of the new one, freeing the old), and person_destroy. `name` in the
// struct must be a copy: main modifies its buffer after creating the
// person, and the person must not change.
//
// EXPECTED OUTPUT
//     Ada (36)
//     buffer is now: Bob
//     still: Ada (36)
//     renamed: Ada Lovelace (36)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    char *name;
    int age;
};

struct person *person_create(const char *name, int age)
{
    // TODO
    (void)name;
    (void)age;
    return NULL;
}

int person_rename(struct person *p, const char *new_name)
{
    // TODO: returns 0 on success, -1 if allocation fails.
    (void)p;
    (void)new_name;
    return -1;
}

void person_destroy(struct person *p)
{
    // TODO
    (void)p;
}

int main(void)
{
    char buffer[16] = "Ada";
    struct person *p = person_create(buffer, 36);

    if (p == NULL) {
        return 1;
    }
    printf("%s (%d)\n", p->name, p->age);
    strcpy(buffer, "Bob");
    printf("buffer is now: %s\n", buffer);
    printf("still: %s (%d)\n", p->name, p->age);
    if (person_rename(p, "Ada Lovelace") != 0) {
        person_destroy(p);
        return 1;
    }
    printf("renamed: %s (%d)\n", p->name, p->age);
    person_destroy(p);
    return 0;
}
