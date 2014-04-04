#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int verbose = 1;
static int spam = 0;

struct puzzle
{
    int value[81];
    int candidate[729];
    int candidate_count[81];
    int row_has[81];
    int col_has[81];
    int box_has[81];
};

#define V(I,J) puzzle->value[((I)-1)*9 + ((J)-1)]
#define C(I,J,K) puzzle->candidate[((I)-1)*81 + ((J)-1)*9 + (K-1)]
#define M(I,J) puzzle->candidate_count[((I)-1)*9 + ((J)-1)]

/* box index has two parts. (X,Y) indicates which of the 9 boxes, and
 * (I,J) indicates which of the 9 slots within the box. */
#define BV(X,Y,I,J)   V( ((X)-1)*3+((I)-1), ((Y)-1)*3+((J)-1)   )
#define BC(X,Y,I,J,K) C( ((X)-1)*3+((I)-1), ((Y)-1)*3+((J)-1), K)
#define BM(X,Y,I,J)   M( ((X)-1)*3+((I)-1), ((Y)-1)*3+((J)-1)   )

#define ROW_HAS(I,V)   puzzle->row_has[ ((I)-1)*9 + (V) ]
#define COL_HAS(J,V)   puzzle->col_has[ ((J)-1)*9 + (V) ]
#define BOX_HAS(X,Y,V) puzzle->box_has[ (((X)-1)*3 + ((Y)-1)) * 9 + (V) ]

#define X_FROM_I(I)    ((((I)-1)/3)+1)
#define Y_FROM_J(J)    ((((J)-1)/3)+1)

#define BOX_OF_IJ_HAS(I,J,V) BOX_HAS( X_FROM_I(I), Y_FROM_J(J), (V) )

void print_puzzle(struct puzzle * puzzle, const char * label)
{
    int i, j;
    printf("--Puzzle: %s\n", label);
    for (i=1; i <= 9; ++i)
    {
        for (j=1; j <= 9; ++j)
        {
            if (V(i,j) > 0)
            {
                printf("  %d ", V(i,j));
            }
            else
            {
                printf(" {%d}", M(i,j));
            }
        }
        printf("\n");
    }
}

void load_puzzle(int expected_id, FILE * fs, struct puzzle * puzzle)
{
    char line[16];
    int id;
    int i, j;
    fscanf(fs, "%s %d", line, &id);
    if (0 != strcmp("Grid", line))
    {
        printf("Expected Grid, got %s\n", line);
        exit(EXIT_FAILURE);
    }
    if (expected_id != id)
    {
        printf("Expected id %d, got %d\n", expected_id, id);
        exit(EXIT_FAILURE);
    }
    memset(puzzle, 0, sizeof(puzzle[0]));
    for (i=1; i <= 9; ++i)
    {
        fscanf(fs, "%s", line);
        if (strlen(line) != 9)
        {
            printf("strlen(%s) is %zu, should be 9\n", line, strlen(line));
            exit(EXIT_FAILURE);
        }
        for (j=1; j <= 9; ++j)
        {
            V(i,j) = (int)(line[j-1]-'0');
            ROW_HAS(i,V(i,j)) = 1;
            COL_HAS(j,V(i,j)) = 1;
            BOX_OF_IJ_HAS(i, j, V(i,j)) = 1;
        }
    }
}

void fill_candidates(struct puzzle * puzzle)
{
    int i, j, k;
    for (i=1; i <= 9; ++i)
    {
        for (j=1; j <= 9; ++j)
        {
            for (k=1; k <= 9; ++k)
            {
                C(i,j,k) = (V(i,j) == 0) ? 1 : 0;
            }
            M(i,j) = (V(i,j) == 0) ? 9 : 0;
        }
    }
    print_puzzle(puzzle, __FUNCTION__);
}

int eliminate_clashes(struct puzzle * puzzle)
{
    int i, j, v;
    int count;
    count = 0;
    for (i=1; i <= 9; ++i)
    {
        for (j=1; j <= 9; ++j)
        {
            if (V(i,j) > 0)
                continue;
            for (v = 1; v <= 9; ++v)
            {
                if (C(i,j,v))
                {
                    if (   ROW_HAS(i, v)
                        || COL_HAS(j, v)
                        || BOX_OF_IJ_HAS(i,j, v) )
                    {
                        C(i,j,v) = 0;
                        M(i,j) -= 1;
                        count += 1;
                    }
                }
            }
        }
    }
    print_puzzle(puzzle, __FUNCTION__);
    return count;
}

int confirm_lonely_hearts(struct puzzle * puzzle)
{
    int i, j, k, count;
    count = 0;
    for (i=1; i <= 9; ++i)
    {
        for (j=1; j <= 9; ++j)
        {
            if (M(i,j) == 1)
            {
                for (k=1; k <= 9; ++k)
                {
                    if (C(i,j,k))
                    {
                        C(i,j,k) = 0;
                        M(i,j) -= 1;
                        V(i,j) = k;
                        ROW_HAS(i, k);
                        COL_HAS(j, k);
                        BOX_OF_IJ_HAS(i,j, k);
                        count += 1;
                        break;
                    }
                }
            }
        }
    }
    print_puzzle(puzzle, __FUNCTION__);
    return count;
}

int main(void)
{
    FILE * fs;
    struct puzzle puzzle;
    int id;
    int count;

    fs = fopen("sudoku.txt", "r");
    if (fs == NULL)
        exit(EXIT_FAILURE);
    for (id=1; id <= 1; ++id)
    {
        if (verbose)
            printf("Puzzle %d\n", id);
        load_puzzle(id, fs, &puzzle);
        fill_candidates(&puzzle);

        do {
            count = confirm_lonely_hearts(&puzzle);
            if (verbose)
                printf("confirmed %d\n", count);
            count = eliminate_clashes(&puzzle);
            if (verbose)
                printf("eliminated %d\n", count);
            sleep(1);
        } while (count > 0);
    }

    exit(EXIT_SUCCESS);
}
