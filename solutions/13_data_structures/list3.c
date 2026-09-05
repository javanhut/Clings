// list3.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *reverse(struct node *head)
{
    struct node *prev = NULL;
    struct node *cur = head;

    while (cur != NULL) {
        struct node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

bool insert_sorted(struct node **head, int value)
{
    struct node *n = malloc(sizeof *n);

    if (n == NULL) {
        return false;
    }
    n->value = value;

    struct node **pp = head;
    while (*pp != NULL && (*pp)->value < value) {
        pp = &(*pp)->next;
    }
    n->next = *pp;
    *pp = n;
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
