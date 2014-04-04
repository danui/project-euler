#ifndef SUDOKU_H
#define SUDOKU_H

struct sudoku;

struct sudoku * new_sudoku(void);

void sudoku_free(struct sudoku * S);

void sudoku_reset(struct sudoku * S);

void sudoku_put(struct sudoku * S, int i, int j, int value);

int sudoku_get(struct sudoku * S, int i, int j);

/**
 * Solve sudoku problem S.
 *
 * @param on_put [in] If set, this callback will be invoked each time
 * the solver finds a value to put.
 */
void sudoku_solve(struct sudoku * S,
    void (*on_put)(struct sudoku * S, int i, int j, int value));

#endif
