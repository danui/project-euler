#include <stdlib.h>
#include "slot.h"
#include "fmt.h"

struct sudoku_slot
{
    int id;
    int row;
    int col;
    int number;
    int has_candidate[10];
    int candidate_count;
    struct sudoku_group *group[3];
    int group_count;
};

struct sudoku_slot * new_slot(int id)
{
    struct sudoku_slot * slot = calloc(1, sizeof(struct sudoku_slot));
    int i, v;
    slot->id = id;
    slot->row = sudoku_slot_row_from_id(id);
    slot->col = sudoku_slot_col_from_id(id);
    slot->number = 0;
    for (v = 1; v <= 9; ++v)
        slot->has_candidate[v] = 1;
    slot->candidate_count = 9;
    for (i=0; i<3; ++i)
        slot->group[i] = NULL;
    slot->group_count = 0;
    return slot;
}

void sudoku_slot_free(struct sudoku_slot * slot)
{
    free(slot);
}

/**
 * Each slot is associated with 3 groups.  This should be called exactly
 * 3 times with appropriate groups before running sudoku_solve().
 */
void sudoku_slot_register_group(struct sudoku_slot * slot, struct sudoku_group * group)
{
    if (slot->group_count >= 3) {
        fprintf(stderr, __FMT__ "slot group count out of bounds\n", __OUT__);
        exit(EXIT_FAILURE);
    }
    slot->group[slot->group_count++] = group;
}

/**
 * Sets a slots number and removes all candidates.
 */
void sudoku_slot_set_number(struct sudoku_slot * slot, int number)
{
    int v;
    if (slot->number == 0) {
        slot->number = number;
        for (v = 1; v <= 9; ++v)
            slot->has_candidate[v] = 0;
        slot->candidate_count = 0;
    } else if (slot->number != number) {
        fprintf(stderr, __FMT__
            "attempt to reset slot %d (%d,%d) number %d to %d\n",
            __OUT__, slot->id, slot->row, slot->col,
            slot->number, number);
        exit(EXIT_FAILURE);
    } else {
        /* nothing to do */
    }
}

/**
 * @return slot number.  0 means no number.
 */
int sudoku_slot_number(struct sudoku_slot * slot)
{
    return slot->number;
}

/**
 * @return 1 if slot has candidate (1..9)
 */
int sudoku_slot_has_candidate(struct sudoku_slot * slot, int candidate)
{
    return slot->has_candidate[candidate];
}

/**
 * @return number of candidates.  (0..9)
 */
int sudoku_slot_candidate_count(struct sudoku_slot * slot)
{
    return slot->candidate_count;
}
