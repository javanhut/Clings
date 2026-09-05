// list2.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

bool push_back(struct node **head, int value)
{
    struct node *n = malloc(sizeof *n);

    if (n == NULL) {
        return false;
    }
    n->value = value;
    n->next = NULL;

    struct node **pp = head;
    while (*pp != NULL) {
        pp = &(*pp)->next;
    }
    *pp = n;
    return true;
}

size_t length(const struct node *head)
{
    size_t n = 0;

    for (; head != NULL; head = head->next) {
        n++;
    }
    return n;
}

bool contains(const struct node *head, int value)
{
    for (; head != NULL; head = head->next) {
        if (head->value == value) {
            return true;
        }
    }
    return false;
}

bool remove_first(struct node **head, int value)
{
    struct node **pp = head;

    while (*pp != NULL && (*pp)->value != value) {
        pp = &(*pp)->next;
    }
    if (*pp == NULL) {
        return false;
    }
    struct node *doomed = *pp;
    *pp = doomed->next;
    free(doomed);
    return true;
}

static void print(const struct node *head)
{
    for (const struct node *n = head; n != NULL; n = n->next) {
        printf("%d%s", n->value, n->next != NULL ? " -> " : "\n");
    }
}

static void free_list(struct node *head)
{
    while (head != NULL) {
        struct node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    struct node *head = NULL;

    for (int v = 10; v <= 40; v += 10) {
        if (!push_back(&head, v)) {
            free_list(head);
            return 1;
        }
    }
    print(head);
    printf("length %zu\n", length(head));
    printf("contains 30: %s\n", contains(head, 30) ? "yes" : "no");
    printf("contains 35: %s\n", contains(head, 35) ? "yes" : "no");
    printf("removed 10: %s\n", remove_first(&head, 10) ? "yes" : "no");
    printf("removed 30: %s\n", remove_first(&head, 30) ? "yes" : "no");
    printf("removed 99: %s\n", remove_first(&head, 99) ? "yes" : "no");
    print(head);
    printf("length %zu\n", length(head));
    free_list(head);
    return 0;
}
