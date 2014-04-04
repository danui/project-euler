#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sudoku.h"

void print_puzzle(int id, const char * label, struct sudoku * S)
{
    int i, j, value;

    if (label)
        printf("Grid %d: %s\n", id, label);
    else
        printf("Grid %d\n", id);
    for (i=1; i <= 9; ++i)
    {
        for (j=1; j <= 9; ++j)
        {
            value = sudoku_get(S, i, j);
            if (value > 0)
                printf(" %d", value);
            else
                printf(" .");
            if ((j%3)==0)
                printf(" ");
        }
        printf("\n");
        if ((i%3)==0)
            printf("\n");
    }
}

void load_puzzle(int expected_id, FILE * fs, struct sudoku * S)
{
    char line[16];
    int id;
    int i, j;
    sudoku_reset(S);
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
            sudoku_put(S, i, j, (int)(line[j-1]-'0'));
        }
    }
}

int main(void)
{
    FILE * fs;
    int id;
    struct sudoku * S;
    char label[100];

    S = new_sudoku();
    fs = fopen("sudoku.txt", "r");
    if (fs == NULL)
        exit(EXIT_FAILURE);
    for (id=1; id <= 50; ++id)
    {
        load_puzzle(id, fs, S);
        print_puzzle(id, "loaded", S);
    }
    sudoku_free(S);
    exit(EXIT_SUCCESS);
}
