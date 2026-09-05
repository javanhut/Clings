// list1.c
//
// CONCEPT
// A *linked list* is a chain of heap-allocated nodes, each holding a
// value and a pointer to the next node. The last node's `next` is NULL.
// The list itself is just a pointer to the first node (the head); an
// empty list is a NULL head.
//
//     struct node {
//         int value;
//         struct node *next;    // a struct may point to its own type
//     };
//
// Adding at the front is O(1): allocate a node, point it at the current
// head, make it the new head. Because that changes the caller's head
// pointer, the function takes `struct node **head` (pointers8) or
// returns the new head. Freeing walks the chain, saving `next` before
// freeing each node (after free, the node must not be read).
//
// Compared to an array: no resizing, O(1) insert/remove at a known
// position, but O(n) to reach the i-th element and poor cache behavior.
// Lists shine when elements are large, order changes often, or nodes are
// shared between structures.
//
// WHEN YOU USE THIS
// Free lists in allocators, queues of pending work, undo history, the
// hash-map buckets in a later exercise. And interviews.
//
// TASK
// Write push_front, print (values separated by " -> ", or "(empty)")
// and free_list.
//
// EXPECTED OUTPUT
//     (empty)
//     3 -> 2 -> 1

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

bool push_front(struct node **head, int value)
{
    // TODO: allocate a node; return false if malloc fails.
    (void)head;
    (void)value;
    return false;
}

void print(const struct node *head)
{
    // TODO
    (void)head;
}

void free_list(struct node *head)
{
    // TODO
    (void)head;
}

int main(void)
{
    struct node *head = NULL;

    print(head);
    for (int i = 1; i <= 3; i++) {
        if (!push_front(&head, i)) {
            free_list(head);
            return 1;
        }
    }
    print(head);
    free_list(head);
    return 0;
}
