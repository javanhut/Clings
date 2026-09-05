// structs4.c
//
// CONCEPT
// Structs are values. `struct account b = a;` copies every member;
// passing a struct to a function copies it too, and returning one copies
// it back. That is convenient for small structs (a point, a pair) and
// wasteful or wrong for big ones or ones meant to be *updated*.
//
// The rule for choosing:
//     by value            small struct, function only reads it, or
//                         returns a new one (vec2 add)
//     by const pointer    large struct, function only reads it
//     by pointer          function modifies it
//
// Assignment also means a struct containing an array copies the array
// (unlike a bare array, which cannot be assigned), while a struct
// containing a *pointer* copies only the pointer: both copies then share
// what it points to. That is the "shallow copy" question; keep it in
// mind for the memory section.
//
// WHEN YOU USE THIS
// Any function that takes a struct. Getting this wrong produces a
// function that looks like it updates something and silently does not.
//
// TASK
// `deposit` and `withdraw` receive copies, so the balance never changes.
// Fix their signatures and bodies (and the calls). `print_account` only
// reads, so give it a const pointer while you are there.
//
// EXPECTED OUTPUT
//     ada: 100
//     ada: 150
//     insufficient funds
//     ada: 150

#include <stdbool.h>
#include <stdio.h>

struct account {
    const char *owner;
    int balance;
};

void deposit(struct account acc, int amount)
{
    acc.balance += amount;
}

bool withdraw(struct account acc, int amount)
{
    if (amount > acc.balance) {
        return false;
    }
    acc.balance -= amount;
    return true;
}

void print_account(struct account acc)
{
    printf("%s: %d\n", acc.owner, acc.balance);
}

int main(void)
{
    struct account acc = {"ada", 100};

    print_account(acc);
    deposit(acc, 50);
    print_account(acc);
    if (!withdraw(acc, 500)) {
        printf("insufficient funds\n");
    }
    print_account(acc);
    return 0;
}
