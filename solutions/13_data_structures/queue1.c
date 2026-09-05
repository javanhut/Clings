// queue1.c - solution

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define CAPACITY 4

struct queue {
    int items[CAPACITY];
    size_t head;
    size_t count;
};

bool is_empty(const struct queue *q)
{
    return q->count == 0;
}

bool is_full(const struct queue *q)
{
    return q->count == CAPACITY;
}

bool enqueue(struct queue *q, int value)
{
    if (is_full(q)) {
        return false;
    }
    q->items[(q->head + q->count) % CAPACITY] = value;
    q->count++;
    return true;
}

bool dequeue(struct queue *q, int *out)
{
    if (is_empty(q)) {
        return false;
    }
    *out = q->items[q->head];
    q->head = (q->head + 1) % CAPACITY;
    q->count--;
    return true;
}

static void enqueue_range(struct queue *q, int from, int to)
{
    printf("enqueued");
    for (int v = from; v <= to; v++) {
        if (enqueue(q, v)) {
            printf(" %d", v);
        }
    }
    printf("\n");
}

static void dequeue_n(struct queue *q, int n)
{
    printf("dequeued");
    for (int i = 0; i < n; i++) {
        int v;
        if (dequeue(q, &v)) {
            printf(" %d", v);
        }
    }
    printf("\n");
}

int main(void)
{
    struct queue q = {{0}, 0, 0};

    enqueue_range(&q, 1, 4);
    printf("full: %s\n", is_full(&q) ? "yes" : "no");
    dequeue_n(&q, 2);
    enqueue_range(&q, 5, 6);
    dequeue_n(&q, 4);
    printf("empty: %s\n", is_empty(&q) ? "yes" : "no");
    return 0;
}
