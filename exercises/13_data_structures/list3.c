// list3.c
//
// CONCEPT
// Two more list operations that every C programmer should be able to
// write from memory:
//
// Reversing in place: walk the list with three pointers, prev, cur and
// next. For each node, save next, point cur->next back at prev, then
// advance prev and cur. At the end prev is the new head. No allocation.
//
// Inserting in sorted order: walk with a pointer-to-pointer until the
// next node's value is >= the new value (or the end), then splice the
// new node in at that link. This keeps a list sorted at O(n) per insert
// and is the basis of insertion sort on lists and of priority queues in
// small systems.
//
// WHEN YOU USE THIS
// Reversal shows up in undo stacks and in converting between "most
// recent first" and "oldest first". Sorted insertion is how timers,
// scheduled events and small ordered indexes are kept.
//
// TASK
// Write reverse (returns the new head) and insert_sorted.
//
// EXPECTED OUTPUT
//     5 -> 1 -> 9 -> 3
//     reversed: 3 -> 9 -> 1 -> 5
//     sorted: 1 -> 3 -> 4 -> 5 -> 9
//     with 0 and 10: 0 -> 1 -> 3 -> 4 -> 5 -> 9 -> 10

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *reverse(struct node *head)
{
    // TODO
    return head;
}

bool insert_sorted(struct node **head, int value)
{
    // TODO
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

static bool push_front(struct node **head, int value)
{
    struct node *n = malloc(sizeof *n);
    if (n == NULL) {
        return false;
    }
    n->value = value;
    n->next = *head;
    *head = n;
    return true;
}

int main(void)
{
    struct node *head = NULL;
    struct node *sorted = NULL;
    int values[] = {3, 9, 1, 5};

    for (int i = 0; i < 4; i++) {
        if (!push_front(&head, values[i])) {
            return 1;
        }
    }
    print(head);
    head = reverse(head);
    printf("reversed: ");
    print(head);

    for (const struct node *n = head; n != NULL; n = n->next) {
        insert_sorted(&sorted, n->value);
    }
    insert_sorted(&sorted, 4);
    printf("sorted: ");
    print(sorted);
    insert_sorted(&sorted, 10);
    insert_sorted(&sorted, 0);
    printf("with 0 and 10: ");
    print(sorted);

    free_list(head);
    free_list(sorted);
    return 0;
}
