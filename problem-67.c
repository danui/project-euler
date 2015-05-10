/*

Maximum path sum II
Problem 67

By starting at the top of the triangle below and moving to adjacent numbers on
the row below, the maximum total from top to bottom is 23.

       3
      7 4
     2 4 6
    8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom in triangle.txt (right click and 'Save
Link/Target As...'), a 15K text file containing a triangle with one-hundred
rows.

NOTE: This is a much more difficult version of Problem 18. It is not possible to
try every route to solve this problem, as there are 299 altogether! If you could
check one trillion (1012) routes every second it would take over twenty billion
years to check them all. There is an efficient algorithm to solve it. ;o)

*/

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
