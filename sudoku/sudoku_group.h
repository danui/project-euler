#ifndef SUDOKU_GROUP_H
#define SUDOKU_GROUP_H

struct sudoku_slot;
struct sudoku_group;

/**
 * Create an empty sudoku group.
 */
struct sudoku_group * new_sudoku_group(int id);

void sudoku_group_free(struct sudoku_group * group);

int sudoku_group_id(struct sudoku_group * group);

/**
 * Add a slot to a group.  This will also call
 * sudoku_slot_register_group().
 */
void sudoku_group_add_slot(struct sudoku_group * group, struct sudoku_slot * slot);

/**
 * @return slot at index i.  i is 0..8
 */
struct sudoku_slot * sudoku_group_slot(struct sudoku_group * group, int i);

/**
 * Called on group when a number has been set for slot.
 */
void sudoku_group_on_slot_set_number(struct sudoku_group * group,
    struct sudoku_slot * slot);

/**
 * @return 1 if did something, 0 if did nothing.
 */
int sudoku_group_resolve(struct sudoku_group * group);

#endif
