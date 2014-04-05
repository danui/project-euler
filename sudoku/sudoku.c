#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sudoku.h"

#include "slot.h"

struct sudoku
{
    struct slot *slot[81];
};

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

    for (i=0; i<81; ++i) {
        if (S->slot[i])
            slot_free(S->slot[i]);
        S->slot[i] = new_slot(i);
    }
}

void sudoku_put(struct sudoku * S, int row, int col, int number)
{
    int i = slot_id_from_rowcol(row, col);
    slot_set_number(S->slot[i], number);
}

int sudoku_get(struct sudoku * S, int row, int col)
{
    int i = slot_id_from_rowcol(row, col);
    return slot_number(S->slot[i]);
}

void sudoku_solve(struct sudoku * S,
    void (*on_found)(struct sudoku * S, int I, int J, int value))
{
    /* TODO: implement? */
}
