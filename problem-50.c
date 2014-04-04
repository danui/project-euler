/*

The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds to a prime below
one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a
prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most
consecutive primes?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"

int main(void)
{
    struct llu_list * L;
    char * is_prime;
    size_t i, k, m, n;
    unsigned long long sum, p, ans;
    unsigned long long target = 1000000;

    L = llu_primes_less_than(target);
    if (L == NULL) {
        fprintf(stderr, __FMT__ "llu_primes_less_than failed\n", __OUT__);
        exit(EXIT_FAILURE);
    }
    is_prime = calloc(target, 1);
    if (is_prime == NULL)
        exit(EXIT_FAILURE);

    for (i=0; i<L->count; ++i) {
        is_prime[L->at[i]] = 1;
        //printf("%llu\n", L->at[i]);
    }

    m = 0;
    for (k=0; k<L->count; ++k) {
        /* from the k'th prime, find the longest length (n) and the
         * prime (p). */
        sum = 0;
        p = 0;
        n = 0;
        for (i=k; i<L->count; ++i) {
            sum += L->at[i];
            if (sum >= target) {
                break;
            }
            //printf("i: %zu Prime: %10llu Sum: %10llu IsPrime: %s\n", i, L->at[i], sum, is_prime[sum]?"yes":"no");
            if (is_prime[sum]) {
                n = i-k+1;
                p = sum;
            }
        }
        /* if n is longer than m, then record p as the ans, and n as the
         * new m. */
        if (n > m) {
            ans = p;
            m = n;
            printf("new winner is prime %llu length %zu\n", ans, m);
        }
    }

    printf("ans: %llu\n", ans);

    llu_list_free(L);
    return 0;
}
