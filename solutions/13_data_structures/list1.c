// list1.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

bool push_front(struct node **head, int value)
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

void print(const struct node *head)
{
    if (head == NULL) {
        printf("(empty)\n");
        return;
    }
    for (const struct node *n = head; n != NULL; n = n->next) {
        printf("%d%s", n->value, n->next != NULL ? " -> " : "\n");
    }
}

void free_list(struct node *head)
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
