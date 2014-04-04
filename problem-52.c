#include <stdio.h>
#include <string.h>

/*
 * Problem 52
 *
 * It can be seen that the number, 125874, and its double, 251748,
 * contain exactly the same digits, but in a different order.
 *
 * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and
 * 6x, contain the same digits.
 *
 */

/*
 * Well... for starters, the first digit is 1 because 2*6 is 12 and that
 * would mean that the 6x version would have more digits.
 *
 * This is the numerical version of the anagram problem.  We need a way
 * to check if x, 2x, 3x, 4x, 5x, and 6x have the same digits.  The way
 * we can get this is by building a histogram that indicates the count
 * of each digit 0-9.  Two numbers with the same histogram therefore
 * have the same digits.
 *
 * A histogram is an array of 10 integers.
 */

struct hist
{
    int count[10];
};

struct hist hist_from_int(int n)
{
    struct hist h;
    int i;
    for (i=0; i<10; ++i)
        h.count[i] = 0;
    while (n > 0) {
        h.count[n%10] += 1;
        n /= 10;
    }
    return h;
}

int satisfies(int n)
{
    struct hist h;
    struct hist k;
    int i;

    h = hist_from_int(n);
    for (i=2; i<=6; ++i) {
        k = hist_from_int(n*i);
        if (0 != memcmp(&h, &k, sizeof(h)))
            return 0;
    }
    return 1;
}

void present_hist(struct hist h)
{
    int i;
    printf("[%d", h.count[0]);
    for (i=1; i<10; ++i)
        printf(", %d", h.count[i]);
    printf("]");
}

int main(void)
{
    int x;
    for (x=1;1;++x) {
        if (satisfies(x)) {
            printf(
                " x: %d\n"
                "2x: %d\n"
                "3x: %d\n"
                "4x: %d\n"
                "5x: %d\n"
                "6x: %d\n"
                , x, x*2, x*3, x*4, x*5, x*6
            );
            return 0;
        }
    }
}
