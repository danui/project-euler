#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "util.h"

void try_num(unsigned long long i)
{
    if (is_prime(i))
    {
        printf("%llu is prime\n", i);
    }
}

int main(void)
{
    unsigned long long i;
    for (i=0LLU; i < 1000LLU; ++i)
        try_num(i);
    return 0;
}
