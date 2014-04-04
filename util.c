#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"


struct llu_list * llu_list_make(size_t capacity)
{
    struct llu_list * L = NULL;
    L = calloc(1, sizeof(struct llu_list));
    if (L == NULL)
        goto error;
    L->at = calloc(capacity, sizeof(unsigned long long));
    if (L->at == NULL)
        goto error;
    L->count = 0;
    L->capacity = capacity;

    return L;
error:
    llu_list_free(L);
    return NULL;
}

void llu_list_free(struct llu_list * L)
{
    if (L) {
        free(L->at);
        free(L);
    }
}

void llu_list_append(struct llu_list * L, unsigned long long val)
{
    if (L->count < L->capacity) {
        L->at[L->count++] = val;
    } else {
        fprintf(stderr, __FMT__ "list is full\n", __OUT__);
        exit(EXIT_FAILURE);
    }
}

struct llu_list * llu_primes_less_than(unsigned long long N)
{
    unsigned char * S;
    struct llu_list * L;
    unsigned long long i, j;

    L = llu_list_make(N/2);
    if (L == NULL)
        return NULL;

    if (N >= 2)
        llu_list_append(L, 2);

    S = calloc(N, 1);
    if (S == NULL) {
        llu_list_free(L);
        return NULL;
    }

    for (i=3; i<N; i += 2) {
        if (!S[i]) {
            llu_list_append(L, i);
            for (j=0; j < N; j += i) {
                S[j] = 1;
            }
        }
    }
    return L;
}

int is_prime(unsigned long long n)
{
    unsigned long long i;
    switch (n) {
        case 0: return 0;
        case 1: return 0;
        case 2: return 1;
        case 3: return 1;
        case 4: return 0;
        case 5: return 1;
    }
    switch (n%6) {
        case 0:                 /* multiple of 6 */
        case 2:                 /* multiple of 2 */
        case 3:                 /* multiple of 3 */
        case 4:                 /* multiple of 2 */
            return 0;
    }
    /* case 1 and 5, possible prime.  We test divisibility below only
     * with other possible primes. */
    for (i=5; (i)*(i) <= n; i += 6)
    {
        if ((n%(i)) == 0) return 0;
        if ((n%(i+2)) == 0) return 0;
    }
    return 1;
}
