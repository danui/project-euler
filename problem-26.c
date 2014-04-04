#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define SEQ_LEN 10000

static size_t recurring_length(int d, int * in_seq)
{
    int n;
    size_t k;

    memset(in_seq, 0, 10000*sizeof(int));
    k = 1;
    n = 1;
    for (;;) {
        if (in_seq[n])
            return k - in_seq[n];
        in_seq[n] = k;
        //printf("k=%zu -> %d\n", k, n);
        n *= 10;
        n = n % d;
        ++k;
    }
}

/* http://projecteuler.net/thread=26;page=8  see "Life"
 *
 * This only works if d is prime.
 */
static size_t recurring_length_2(int d, int * in_seq)
{
    int n = 10;
    size_t k = 1;
    while (n != 0 && n != 1) {
        n = (n * 10) % d;
        ++k;
    }
    return k;
}

int main(void)
{
    int d;
    size_t max_len = 0;
    size_t len;
    int * in_seq;
    int d_at_max;
    struct llu_list * d_list;
    size_t i;

    in_seq = malloc(SEQ_LEN * sizeof(int));
    if (in_seq == NULL)
        exit(EXIT_FAILURE);

#define USE_PRIMES 0
#if USE_PRIMES
    d_list = llu_primes_less_than(1000);
    d = d_list->at[0];
    for (i=0,d=d_list->at[i]; i < d_list->count; ++i,d=d_list->at[i])
#else
    for (d=1; d < 1000; ++d)
#endif
    {
#if USE_PRIMES
        len = recurring_length_2(d, in_seq);
#else
        len = recurring_length(d, in_seq);
#endif
        if (max_len < len) {
            max_len = len;
            d_at_max = d;
            //printf("1/%d => %zu    *** NEW MAX ***\n", d, len);
        } else {
            //printf("1/%d => %zu\n", d, len);
        }
        if (d==110)
            printf("1/%d => %zu\n", d, len);
    }
    printf("1/%d => %zu\n", d_at_max, max_len);
    exit(EXIT_SUCCESS);
}


