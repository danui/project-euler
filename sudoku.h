#ifndef SUDOKU_H
#define SUDOKU_H

struct sudoku;

struct sudoku * new_sudoku(void);

void sudoku_free(struct sudoku * S);

void sudoku_reset(struct sudoku * S);

/**
 * Put value at (I,J).  I and J are 1-based indices; i.e. 1..9
 */
void sudoku_put(struct sudoku * S, int I, int J, int value);

int sudoku_get(struct sudoku * S, int I, int J);

/**
 * Solve sudoku problem S.
 *
 * @param on_found [in] If set, this callback will be invoked each time
 * the solver finds a value to put.
 */
void sudoku_solve(struct sudoku * S,
    void (*on_found)(struct sudoku * S, int I, int J, int value));

#endif
