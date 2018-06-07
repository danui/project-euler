/*

Problem 48

The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... +
1000^1000.

*/

#include <stdio.h>

int main(void)
{
    unsigned long long sum, num, i, j, N, base;

    /* last ten digits basically means modulo 10000000000LLU */
    base = 10000000000LLU;
    N = 1000;
    sum = 0;
    for (i=1; i <= N; ++i) {
        num = 1;
        for (j=0; j < i; ++j) {
            num = (num * i) % base;
        }
        sum = (sum + num) % base;
    }
    printf("%llu\n", sum);

    return 0;
}
