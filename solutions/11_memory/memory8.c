// memory8.c - solution

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    char *name;
    int age;
};

static char *copy_string(const char *s)
{
    size_t size = strlen(s) + 1;
    char *copy = malloc(size);

    if (copy != NULL) {
        memcpy(copy, s, size);
    }
    return copy;
}

struct person *person_create(const char *name, int age)
{
    struct person *p = malloc(sizeof *p);

    if (p == NULL) {
        return NULL;
    }
    p->name = copy_string(name);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    p->age = age;
    return p;
}

int person_rename(struct person *p, const char *new_name)
{
    char *copy = copy_string(new_name);

    if (copy == NULL) {
        return -1;
    }
    free(p->name);
    p->name = copy;
    return 0;
}

void person_destroy(struct person *p)
{
    if (p == NULL) {
        return;
    }
    free(p->name);
    free(p);
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
