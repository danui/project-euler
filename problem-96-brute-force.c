#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int grid[81];
#define G(I,J) grid[(I)*9+(J)]

void reset_grid(void)
{
    memset(grid, 0, 81 * sizeof(int));
}

void print_puzzle(int id, const char * label)
{
    int i, j, value;

    if (label)
        printf("Grid %d: %s\n", id, label);
    else
        printf("Grid %d\n", id);
    for (i=0; i < 9; ++i)
    {
        for (j=0; j < 9; ++j)
        {
            value = G(i,j);
            if (value > 0)
                printf(" %d", value);
            else
                printf(" .");
            if ((j%3)==(3-1))
                printf(" ");
        }
        printf("\n");
        if ((i%3)==(3-1))
            printf("\n");
    }
}

void load_puzzle(int expected_id, FILE * fs)
{
    char line[16];
    int id;
    int i, j;
    fscanf(fs, "%s %d", line, &id);
    if (0 != strcmp("Grid", line))
    {
        printf("Expected Grid, got %s\n", line);
        exit(EXIT_FAILURE);
    }
    if (expected_id != id)
    {
        printf("Expected id %d, got %d\n", expected_id, id);
        exit(EXIT_FAILURE);
    }
    for (i=0; i < 9; ++i)
    {
        fscanf(fs, "%s", line);
        if (strlen(line) != 9)
        {
            printf("strlen(%s) is %zu, should be 9\n", line, strlen(line));
            exit(EXIT_FAILURE);
        }
        for (j=0; j < 9; ++j)
        {
            G(i,j) = (int)(line[j]-'0');
        }
    }
}

/**
 * @return 1 if G(i,j) does not voilate rules.
 */
int is_okay(int i, int j)
{
    int k, a, b;
    if (G(i,j) == 0)
        return 0;
    for (k=0; k<9; ++k) {
        if (k != i)
            if (G(k,j) == G(i,j))
                return 0;
        if (k != j)
            if (G(i,k) == G(i,j))
                return 0;
    }
    for (a = i/3*3; a < i/3*3+3; ++a)
        for (b = j/3*3; b < j/3*3+3; ++b)
            if (a != i || b != j)
                if (G(a,b) == G(i,j))
                    return 0;
    return 1;
}

int solve_puzzle(int u)
{
    int i=u/9;
    int j=u%9;
    int k;

    if (u == 81)
        return 1;

    if (grid[u] != 0)
        return solve_puzzle(u+1);

    for (k=1; k<=9; ++k) {
        grid[u] = k;
        if (is_okay(i,j))
            if (solve_puzzle(u+1))
                return 1;
    }
    grid[u] = 0;
    return 0;
}

int main(void)
{
    FILE * fs;
    int id;
    char label[100];
    int sum;

    fs = fopen("sudoku.txt", "r");
    if (fs == NULL)
        exit(EXIT_FAILURE);
    sum = 0;
    for (id=1; id <= 50; ++id)
    {
        reset_grid();
        load_puzzle(id, fs);
        print_puzzle(id, "loaded");
        if (!solve_puzzle(0)) {
            printf("Failed to solve puzzle %d\n", id);
            print_puzzle(id, "error");
            exit(EXIT_FAILURE);
        }
        print_puzzle(id, "solved");
        sum += grid[0]*100 + grid[1]*10 + grid[2];
        printf("sum: %d\n", sum);
    }
    exit(EXIT_SUCCESS);
}
