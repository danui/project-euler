#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sudoku.h"

#include "sudoku_slot.h"
#include "sudoku_group.h"

struct sudoku
{
    struct sudoku_slot *slot[81];
    struct sudoku_group *group[27];
};

static void link_group_slot(struct sudoku * S, int g, int s)
{
    struct sudoku_group * group = S->group[g];
    struct sudoku_slot * slot = S->slot[s];
    sudoku_group_add_slot(group, slot);
    sudoku_slot_add_group(slot, group);
}

struct sudoku * new_sudoku(void)
{
    struct sudoku * S = calloc(1, sizeof(struct sudoku));
    int i, j, k;
    for (i=0; i<81; ++i)
        S->slot[i] = new_slot(i);
    for (i=0; i<27; ++i)
        S->group[i] = new_sudoku_group(i);

    // create group-slot relationships
    k = 0; // group id

    // add rows
    for (i=0; i<9; ++i) {
        for (j=0; j<9; ++j) {
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i,j));
        }
        k += 1;
    }

    // add cols
    for (j=0; j<9; ++j) {
        for (i=0; i<9; ++i) {
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i,j));
        }
        k += 1;
    }

    // add boxes
    for (i=0; i<9; i+=3) {
        for (j=0; j<9; j += 3) {
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+0,j+0));
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+1,j+0));
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+2,j+0));

            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+0,j+1));
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+1,j+1));
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+2,j+1));

            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+0,j+2));
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+1,j+2));
            link_group_slot(S, k, sudoku_slot_id_from_rowcol(i+2,j+2));

            k += 1;
        }
    }

    return S;
}

void sudoku_free(struct sudoku * S)
{
    int i;
    if (S) {
        for (i=0; i<81; ++i)
            sudoku_slot_free(S->slot[i]);
        for (i=0; i<27; ++i)
            sudoku_group_free(S->group[i]);
        free(S);
    }
}

void sudoku_put(struct sudoku * S, int row, int col, int number)
{
    int i = sudoku_slot_id_from_rowcol(row, col);
    sudoku_slot_set_number(S->slot[i], number);
}

int sudoku_get(struct sudoku * S, int row, int col)
{
    int i = sudoku_slot_id_from_rowcol(row, col);
    return sudoku_slot_number(S->slot[i]);
}

void sudoku_solve(struct sudoku * S, struct sudoku_callbacks * callbacks)
{
    /* TODO: implement? */
}
