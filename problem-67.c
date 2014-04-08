#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NROWS 100

int * solve(int n, FILE * in)
{
    int * x = malloc(n*sizeof(int));
    int * y;
    int i;
    for (i=0; i<n; ++i)
        fscanf(in, "%d", x+i);
    if (n < NROWS) {
        y = solve(n+1, in);
        for (i=0; i<n; ++i)
            if (y[i] < y[i+1])
                x[i] += y[i+1];
            else
                x[i] += y[i];
        free(y);
    }
    return x;
}

int main(void)
{
    FILE * in = fopen("triangle.txt", "r");
    int * x;
    x = solve(1, in);
    printf("x[0] = %d\n", x[0]);
    free(x);
    fclose(in);
    return 0;
}
