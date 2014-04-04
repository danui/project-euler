/*

What is the first term in the Fibonacci sequence to contain 1000 digits?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "util.h"

void add(unsigned char *X, unsigned char *Y, unsigned char *Z, size_t n)
{
    size_t i;
    memset(Z, 0, n);
    for (i=0; i<n; ++i)
    {
        Z[i] = Z[i] + X[i] + Y[i];
        if (Z[i] > 9) {
            Z[i+1] = Z[i] / 10;
            Z[i]   = Z[i] % 10;
        }
    }
}

int main(void)
{
    const size_t K = 1000;
    unsigned char A[3][K];
    size_t n, x, y, z, i;

    x = 0;
    y = 1;
    z = 2;

    memset(A[x], 0, K);
    memset(A[y], 0, K);
    memset(A[z], 0, K);

    A[x][0] = 1;
    A[y][0] = 1;
    n = 2;
    while (A[y][K-1] == 0)
    {
        add(A[x], A[y], A[z], K);
        x = (x+1)%3;
        y = (y+1)%3;
        z = (z+1)%3;
        n += 1;
    }

    printf("n=%zu\n", n);
    if (0)
    {
        for (i=0; i<K; ++i)
        {
            printf("%u", A[y][K-1-i]);
        }
        printf("\n");
    }
    return 0;
}
