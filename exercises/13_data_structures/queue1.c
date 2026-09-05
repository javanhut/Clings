// queue1.c
//
// CONCEPT
// A *queue* is first-in, first-out. A *ring buffer* implements a
// fixed-capacity queue with no allocation and no shifting: an array,
// a `head` index (where the next dequeue reads), a `count`, and the
// arithmetic `(head + count) % capacity` for where the next enqueue
// writes. Indices wrap around the end of the array, hence "ring".
//
//     enqueue: if count == capacity -> full
//              items[(head + count) % capacity] = x; count++
//     dequeue: if count == 0 -> empty
//              x = items[head]; head = (head + 1) % capacity; count--
//
// Some implementations keep head and tail instead of a count and waste
// one slot to tell full from empty; the count version is simpler.
//
// WHEN YOU USE THIS
// Ring buffers are everywhere in systems code: keyboard and serial
// input, audio, network packet queues, logging, producer/consumer
// between threads or interrupt handlers. Fixed memory, O(1) both ends,
// and no pointers to go wrong.
//
// TASK
// Write enqueue, dequeue, is_empty and is_full for the ring buffer, then
// run the scenario in main.
//
// EXPECTED OUTPUT
//     enqueued 1 2 3 4
//     full: yes
//     dequeued 1 2
//     enqueued 5 6
//     dequeued 3 4 5 6
//     empty: yes

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
    // TODO
    (void)q;
    return true;
}

bool is_full(const struct queue *q)
{
    // TODO
    (void)q;
    return false;
}

bool enqueue(struct queue *q, int value)
{
    // TODO
    (void)q;
    (void)value;
    return false;
}

bool dequeue(struct queue *q, int *out)
{
    // TODO
    (void)q;
    (void)out;
    return false;
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
