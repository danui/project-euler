#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sudoku.h"

struct slot;
struct group;

struct slot {
    int id;
    int number;
    int * has_candidate;
    int num_candidates;
    struct group ** groups;
};

void slot_init(struct slot * slot, int id);
void slot_put(struct slot * slot, int number);
void slot_candidates(struct slot * slot, int * ret_candidates);



struct sudoku {
    int value_grid[9*9];
    int candidate_grid[9*9*9];
    int num_values;
    //struct subproblem * subproblems;
    int subproblem_grid[9*9*3];
};



void foreach_subproblem(struct sudoku * S, int i, int j,
    void (*subproblem)(struct sudoku * S, int ib, int ic, int jb, int jc))
{
    subproblem(S, i, 1, 0, 9);
    subproblem(S, 0, 9, j, 1);
    subproblem(S, i/3*3, 3, j/3*3, 3);
}



struct sudoku * new_sudoku(void)
{
    struct sudoku * S = calloc(1, sizeof(struct sudoku));
    sudoku_reset(S);
    return S;
}

void sudoku_free(struct sudoku * S)
{
    if (S) {
        free(S);
    }
}

void sudoku_reset(struct sudoku * S)
{
    int i, j, k;
    memset(S, 0, sizeof(struct sudoku));
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j)
            for (k=0; k<9; ++k)
                S->candidate_grid[i*9*9 + j*9 + k] = 1;
}

void sudoku_put(struct sudoku * S, int I, int J, int value)
{
    int i = I-1;
    int j = J-1;
    int k = value - 1;
    S->value_grid[i*9+j] = value;
    S->num_values += 1;
}

int sudoku_get(struct sudoku * S, int I, int J)
{
    int i = I-1;
    int j = J-1;
    return S->value_grid[i*9 + j];
}

void sudoku_solve(struct sudoku * S,
    void (*on_found)(struct sudoku * S, int I, int J, int value))
{
    /* TODO: implement? */
    for (T = S->subproblems; T != NULL; T = T->next) {
        resolve(T, S);
    }
}
