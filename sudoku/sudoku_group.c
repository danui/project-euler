#include <stdlib.h>


#include "fmt.h"
#include "sudoku_group.h"
#include "sudoku_slot.h"

struct sudoku_group
{
    struct sudoku_slot *slot[9];
    int id;
    int slot_count;
};

/**
 * Create an empty sudoku group.
 */
struct sudoku_group * new_sudoku_group(int id)
{
    struct sudoku_group * group = calloc(1, sizeof(struct sudoku_group));
    group->id = id;
    group->slot_count = 0;
    return group;
}

void sudoku_group_free(struct sudoku_group * group)
{
    free(group);
}

int sudoku_group_id(struct sudoku_group * group)
{
    return group->id;
}

/**
 * Add a slot to a group.
 */
void sudoku_group_add_slot(struct sudoku_group * group, struct sudoku_slot * slot)
{
    if (group->slot_count == 9) {
        fprintf(stderr, __FMT__ "too many slots! group %d slot %d\n",
            __OUT__, sudoku_group_id(group), sudoku_slot_id(slot));
        exit(EXIT_FAILURE);
    }
    group->slot[group->slot_count++] = slot;
}

/**
 * @return slot at index i.  i is 0..8
 */
struct sudoku_slot * sudoku_group_slot(struct sudoku_group * group, int i)
{
    return group->slot[i];
}

void sudoku_group_on_slot_set_number(struct sudoku_group * group,
    struct sudoku_slot * slot)
{
    int number = sudoku_slot_number(slot);
    int i;
    for (i=0; i < group->slot_count; ++i)
        sudoku_slot_remove_candidate(group->slot[i], number);
}

int sudoku_group_resolve(struct sudoku_group * group)
{
    int ret = 0;
    int k, i, j, n;

    for (k=1; k<=9; ++k) {
        n = 0;
        for (i=0; i<9; ++i) {
            if (sudoku_slot_has_candidate(group->slot[i], k)) {
                n += 1;
                j = i;
            }
        }
        if (n == 1) {
            /* then k is present only at slot j. */
            sudoku_slot_set_number(group->slot[j], k);
            ret = 1;
        }
    }

    /* TODO: This needs to be improved... */

    return ret;
}
