#ifndef SUDOKU_SLOT_H
#define SUDOKU_SLOT_H

struct group;
struct slot;

static inline int slot_row_from_id(int id)
{
    return id / 9;
}

static inline int slot_col_from_id(int id)
{
    return id % 9;
}

static inline int slot_id_from_rowcol(int row, int col)
{
    return row * 9 + col;
}

struct slot * new_slot(int id);
void slot_free(struct slot * slot);

/**
 * Each slot is associated with 3 groups.  This should be called exactly
 * 3 times with appropriate groups before running sudoku_solve().
 */
void slot_register_group(struct slot * slot, struct group * group);

/**
 * Sets a slots number and removes all candidates.
 */
void slot_set_number(struct slot * slot, int number);

/**
 * @return slot number.  0 means no number.
 */
int slot_number(struct slot * slot);

/**
 * @return 1 if slot has candidate (1..9)
 */
int slot_has_candidate(struct slot * slot, int candidate);

/**
 * @return number of candidates.  (0..9)
 */
int slot_candidate_count(struct slot * slot);

#endif
