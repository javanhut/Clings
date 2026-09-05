// switch2.c - solution

#include <stdbool.h>
#include <stdio.h>

int days_in_month(int month, bool leap)
{
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return leap ? 29 : 28;
    default:
        return -1;
    }
}

int main(void)
{
    printf("month 1: %d days\n", days_in_month(1, false));
    printf("month 2: %d days\n", days_in_month(2, false));
    printf("month 2 (leap): %d days\n", days_in_month(2, true));
    printf("month 4: %d days\n", days_in_month(4, false));
    printf("month 12: %d days\n", days_in_month(12, false));
    printf("month 13: %d days\n", days_in_month(13, false));
    return 0;
}
