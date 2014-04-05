#ifndef SUDOKU_SLOT_H
#define SUDOKU_SLOT_H

struct sudoku_group;
struct sudoku_slot;

static inline int sudoku_slot_row_from_id(int id)
{
    return id / 9;
}

static inline int sudoku_slot_col_from_id(int id)
{
    return id % 9;
}

static inline int sudoku_slot_id_from_rowcol(int row, int col)
{
    return row * 9 + col;
}

struct sudoku_slot * new_slot(int id);
void sudoku_slot_free(struct sudoku_slot * slot);

/**
 * Each slot is associated with 3 groups.  This should be called exactly
 * 3 times with appropriate groups before running sudoku_solve().
 */
void sudoku_slot_register_group(struct sudoku_slot * slot, struct sudoku_group * group);

/**
 * Sets a slots number and removes all candidates.
 */
void sudoku_slot_set_number(struct sudoku_slot * slot, int number);

/**
 * @return slot number.  0 means no number.
 */
int sudoku_slot_number(struct sudoku_slot * slot);

/**
 * @return 1 if slot has candidate (1..9)
 */
int sudoku_slot_has_candidate(struct sudoku_slot * slot, int candidate);

/**
 * @return number of candidates.  (0..9)
 */
int sudoku_slot_candidate_count(struct sudoku_slot * slot);

#endif
