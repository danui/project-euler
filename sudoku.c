#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sudoku.h"

struct sudoku {
    int * value_grid;
};

struct sudoku * new_sudoku(void)
{
    struct sudoku * S = calloc(1, sizeof(struct sudoku));
    S->value_grid = calloc(81, sizeof(int));
    return S;
}

void sudoku_free(struct sudoku * S)
{
    if (S) {
        free(S->value_grid);
        free(S);
    }
}

void sudoku_reset(struct sudoku * S)
{
    memset(S->value_grid, 0, 9*9);
}

void sudoku_put(struct sudoku * S, int i, int j, int value)
{
    S->value_grid[(i-1)*9+(j-1)] = value;
}

int sudoku_get(struct sudoku * S, int i, int j)
{
    return S->value_grid[(i-1)*9+(j-1)];
}

void sudoku_solve(struct sudoku * S,
    void (*on_put)(struct sudoku * S, int i, int j, int value))
{
    /* TODO: implement? */
}
