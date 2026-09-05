// structs4.c - solution

#include <stdbool.h>
#include <stdio.h>

struct account {
    const char *owner;
    int balance;
};

void deposit(struct account *acc, int amount)
{
    acc->balance += amount;
}

bool withdraw(struct account *acc, int amount)
{
    if (amount > acc->balance) {
        return false;
    }
    acc->balance -= amount;
    return true;
}

void print_account(const struct account *acc)
{
    printf("%s: %d\n", acc->owner, acc->balance);
}

int main(void)
{
    struct account acc = {"ada", 100};

    print_account(&acc);
    deposit(&acc, 50);
    print_account(&acc);
    if (!withdraw(&acc, 500)) {
        printf("insufficient funds\n");
    }
    print_account(&acc);
    return 0;
}
