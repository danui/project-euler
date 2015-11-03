#ifndef SUDOKU_H
#define SUDOKU_H

struct sudoku;

struct sudoku * new_sudoku(void);

void sudoku_free(struct sudoku * S);

/**
 * Put number at (row,col).  row and col are 0..8.
 */
void sudoku_put(struct sudoku * S, int row, int col, int value);

/**
 * @return number at (row,col).
 */
int sudoku_get(struct sudoku * S, int row, int col);

struct sudoku_callbacks
{
    /**
     * If provided, this callback will be invoked when sudoku_solve()
     * finds a number to put into slot (row,col).
     */
    void (*on_set_number)(struct sudoku * S, int row, int col, int number);

    /* more callbacks here, as we discover them... */
};

/**
 * Solve sudoku problem S.
 */
void sudoku_solve(struct sudoku * S, struct sudoku_callbacks * callbacks);

#endif
