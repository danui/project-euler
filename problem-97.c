/*
 * Problem 97
 *
 * The first known prime found to exceed one million digits was
 * discovered in 1999, and is a Mersenne prime of the form 2^6972593−1;
 * it contains exactly 2,098,960 digits. Subsequently other Mersenne
 * primes, of the form 2^p−1, have been found which contain more digits.
 *
 * However, in 2004 there was found a massive non-Mersenne prime which
 * contains 2,357,207 digits: 28433×2^7830457+1.
 *
 * Find the last ten digits of this prime number.
 */

#include <stdio.h>
int main(void)
{
    unsigned long long number;
    int i;
    number = 28433;
    for (i=0; i<7830457; ++i) {
        number *= 2;
        number %= 10000000000ULL;
    }
    number += 1;
    number %= 10000000000ULL;
    printf("28433*2^7830457+1 mod 10000000000ULL is %llu\n", number);
    return 0;
}
