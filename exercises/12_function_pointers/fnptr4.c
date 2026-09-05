// fnptr4.c
//
// CONCEPT
// A *dispatch table* is an array of {name, function} pairs. To run a
// command, search the table for the name and call the function. Adding
// a command means adding one line to the table; no `if` chain grows.
//
//     struct command {
//         const char *name;
//         int (*run)(int, int);
//     };
//     static const struct command commands[] = {
//         {"add", add},
//         {"sub", sub},
//     };
//
// The same idea with an enum index instead of a name search gives a
// jump table, which is how interpreters dispatch opcodes and how the
// "virtual method table" of object-oriented C works: a struct of
// function pointers, one per operation, shared by all objects of a kind.
//
// WHEN YOU USE THIS
// Command-line subcommands, REPLs, protocol message handlers, plugin
// registries, drivers (a `struct file_operations` in the Linux kernel is
// exactly this).
//
// TASK
// Fill in the `commands` table with add, sub, mul and div (integer
// division; return 0 for division by zero and print "error: division by
// zero") and write `run`, which finds the command by name, calls it and
// prints the result, or prints "unknown command: <name>".
//
// EXPECTED OUTPUT
//     add 7 3 = 10
//     sub 7 3 = 4
//     mul 7 3 = 21
//     div 7 3 = 2
//     error: division by zero
//     div 7 0 = 0
//     unknown command: pow

#include <stdio.h>
#include <string.h>

struct command {
    const char *name;
    int (*run)(int, int);
};

// TODO: add, sub, mul, div_ (div is taken by <stdlib.h>, so name it div_)

static const struct command commands[] = {
    // TODO
    {NULL, NULL},
};

void run(const char *name, int a, int b)
{
    // TODO
    (void)name;
    (void)a;
    (void)b;
}

int main(void)
{
    run("add", 7, 3);
    run("sub", 7, 3);
    run("mul", 7, 3);
    run("div", 7, 3);
    run("div", 7, 0);
    run("pow", 7, 3);
    return 0;
}
