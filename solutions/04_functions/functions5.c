// functions5.c - solution

#include <stdbool.h>
#include <stdio.h>

int gcd(int a, int b)
{
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

bool is_prime(int n)
{
    if (n < 2) {
        return false;
    }
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int count_primes_below(int limit)
{
    int count = 0;

    for (int n = 2; n < limit; n++) {
        if (is_prime(n)) {
            count++;
        }
    }
    return count;
}

int main(void)
{
    printf("gcd(48, 18) = %d\n", gcd(48, 18));
    printf("gcd(17, 5) = %d\n", gcd(17, 5));
    printf("gcd(0, 9) = %d\n", gcd(0, 9));
    printf("is_prime(1) = %s\n", is_prime(1) ? "yes" : "no");
    printf("is_prime(2) = %s\n", is_prime(2) ? "yes" : "no");
    printf("is_prime(91) = %s\n", is_prime(91) ? "yes" : "no");
    printf("is_prime(97) = %s\n", is_prime(97) ? "yes" : "no");
    printf("primes below 50: %d\n", count_primes_below(50));
    return 0;
}
