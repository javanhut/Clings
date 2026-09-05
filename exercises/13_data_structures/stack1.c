// stack1.c
//
// CONCEPT
// A *stack* is last-in, first-out: push adds on top, pop removes the
// top. On top of a growable array (memory2) it is trivial: push appends,
// pop decrements the length. Peek looks at the top without removing it.
//
// The classic use is matching nested things. To check that brackets in
// "{[()]}" are balanced: push every opener; on a closer, pop and check
// it matches; at the end the stack must be empty. The same algorithm
// with a richer stack is a parser; with an operand stack it is an RPN
// calculator (the io section has one).
//
// The *call stack* your program runs on is the same idea in hardware:
// each function call pushes a frame with its locals and return address.
//
// WHEN YOU USE THIS
// Parsers, expression evaluation, undo, depth-first search, backtracking.
// Stacks also replace recursion when the depth could blow the call stack.
//
// TASK
// Write stack_push (growing with realloc), stack_pop (returns false when
// empty), stack_free, and `balanced`, which uses the stack to check
// (), [] and {} nesting.
//
// EXPECTED OUTPUT
//     "{[()]}" balanced: yes
//     "([)]" balanced: no
//     "((" balanced: no
//     "" balanced: yes
//     "a(b)c[d]{e}" balanced: yes

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct stack {
    char *items;
    size_t len;
    size_t cap;
};

bool stack_push(struct stack *s, char c)
{
    // TODO
    (void)s;
    (void)c;
    return false;
}

bool stack_pop(struct stack *s, char *out)
{
    // TODO
    (void)s;
    (void)out;
    return false;
}

void stack_free(struct stack *s)
{
    // TODO
    (void)s;
}

bool balanced(const char *text)
{
    // TODO: use a struct stack; free it on every path.
    (void)text;
    return false;
}

int main(void)
{
    const char *samples[] = {"{[()]}", "([)]", "((", "", "a(b)c[d]{e}"};

    for (size_t i = 0; i < 5; i++) {
        printf("\"%s\" balanced: %s\n", samples[i], balanced(samples[i]) ? "yes" : "no");
    }
    return 0;
}
