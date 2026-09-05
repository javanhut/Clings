// list2.c
//
// CONCEPT
// Most list operations are "walk until a condition, then do something".
// Removing a node is the interesting one: you must update the `next`
// pointer of the *previous* node (or the head, if removing the first).
// The naive version has a special case for the head and tracks a `prev`
// pointer. The elegant version walks a *pointer to the pointer* that
// leads to each node:
//
//     struct node **pp = head;          // pp points at the head pointer
//     while (*pp != NULL && (*pp)->value != value)
//         pp = &(*pp)->next;            // now points at some node's next
//     if (*pp != NULL) {
//         struct node *doomed = *pp;
//         *pp = doomed->next;           // unlink: works for head too
//         free(doomed);
//     }
//
// Whether pp points at the head variable or at a node's `next` field,
// `*pp = ...` rewires the right link. No special case.
//
// WHEN YOU USE THIS
// Any singly linked structure: removing, inserting in order, splicing.
// This pointer-to-pointer walk is the idiom that separates people who
// have understood pointers from people who have memorized them.
//
// TASK
// Write push_back (walk to the end; the list may be empty), length,
// contains, and remove_first using the pointer-to-pointer walk (return
// true if something was removed).
//
// EXPECTED OUTPUT
//     10 -> 20 -> 30 -> 40
//     length 4
//     contains 30: yes
//     contains 35: no
//     removed 10: yes
//     removed 30: yes
//     removed 99: no
//     20 -> 40
//     length 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

bool push_back(struct node **head, int value)
{
    // TODO
    (void)head;
    (void)value;
    return false;
}

size_t length(const struct node *head)
{
    // TODO
    (void)head;
    return 0;
}

bool contains(const struct node *head, int value)
{
    // TODO
    (void)head;
    (void)value;
    return false;
}

bool remove_first(struct node **head, int value)
{
    // TODO: pointer-to-pointer walk.
    (void)head;
    (void)value;
    return false;
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
