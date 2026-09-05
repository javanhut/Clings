// types7.c - solution

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool nearly_equal(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}

int main(void)
{
    double sum = 0.0;

    for (int i = 0; i < 10; i++) {
        sum += 0.1;
    }

    printf("sum = %.17g\n", sum);
    printf("sum == 1.0: %s\n", sum == 1.0 ? "yes" : "no");
    printf("nearly_equal(sum, 1.0): %s\n",
           nearly_equal(sum, 1.0, 1e-9) ? "yes" : "no");
    return 0;
}
