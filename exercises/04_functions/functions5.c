// functions5.c
//
// CONCEPT
// A function is a contract: given these inputs, it produces this output,
// and the caller does not care how. Good C is built from small functions
// with one job each, which can be tested by calling them with known inputs
// and printing the results, exactly what `main` does here.
//
// Two classic algorithms to implement:
//   - Euclid's algorithm for the greatest common divisor: while b is not
//     0, replace (a, b) by (b, a % b). When b reaches 0, a is the answer.
//   - Primality by trial division: n is prime when n >= 2 and no d in
//     2..sqrt(n) divides it. Stop the loop when d * d > n; there is no
//     need for the sqrt function.
//
// WHEN YOU USE THIS
// gcd is inside every fraction library and many hashing/scheduling
// tricks; trial division is the first thing in any number-theory code.
// More importantly: this is the shape of most of the code you will write.
// Read a spec, write a function, check it against known values.
//
// TASK
// Write `gcd`, `is_prime` and `count_primes_below` (which uses is_prime).
//
// EXPECTED OUTPUT
//     gcd(48, 18) = 6
//     gcd(17, 5) = 1
//     gcd(0, 9) = 9
//     is_prime(1) = no
//     is_prime(2) = yes
//     is_prime(91) = no
//     is_prime(97) = yes
//     primes below 50: 15

#include <stdbool.h>
#include <stdio.h>

int gcd(int a, int b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

bool is_prime(int n)
{
    // TODO
    (void)n;
    return false;
}

int count_primes_below(int limit)
{
    // TODO: how many n in [0, limit) are prime?
    (void)limit;
    return 0;
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
