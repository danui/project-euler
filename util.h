#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <unistd.h>

#define __FMT__ "%s:%d "
#define __OUT__ __FILE__,__LINE__

struct llu_list
{
    unsigned long long * at;
    size_t count;
    size_t capacity;
};

struct llu_list * llu_list_make(size_t capacity);
void llu_list_free(struct llu_list * llu_list);
void llu_list_append(struct llu_list * llu_list, unsigned long long val);


/**
 * @return prime numbers less than N.
 */
struct llu_list * llu_primes_less_than(unsigned long long N);

/**
 * @return is n prime?
 */
int is_prime(unsigned long long n);

#endif
