/**
 * Problem 23
 * Non-abundant sums
 *
 *     https://projecteuler.net/problem=23
 *
 * A perfect number is a number for which the sum of its proper divisors
 * is exactly equal to the number. For example, the sum of the proper
 * divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28
 * is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors is
 * less than n and it is called abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the
 * smallest number that can be written as the sum of two abundant
 * numbers is 24. By mathematical analysis, it can be shown that all
 * integers greater than 28123 can be written as the sum of two abundant
 * numbers. However, this upper limit cannot be reduced any further by
 * analysis even though it is known that the greatest number that cannot
 * be expressed as the sum of two abundant numbers is less than this
 * limit.
 *
 * Find the sum of all the positive integers which cannot be written as
 * the sum of two abundant numbers.
 */

#include <stdint.h>
#include <stdio.h>
#include "itshould.h"

typedef long long unsigned number_t;

/**
 * @return 1 if divisor is a proper divisor of subject.
 */
static int is_proper_divisor(number_t subject, number_t divisor) {
    return (subject % divisor) == 0 ? 1:0;
}

static number_t sum_of_proper_divisors(number_t x) {
    number_t i;
    number_t j;
    number_t sum;
    number_t upper;

    /* zero is not a perfect number */
    if (x == 0) return 0;

    upper = x / 2;
    sum = 1;
    for (i = 2; i < upper; ++i) {
        j = x / i;
        if (j*i == x) {
            sum += i + j;
        }
        upper = j;
    }
    return sum;
}

enum number_type {
    DEFICIENT = 0,
    PERFECT,
    ABUNDANT
};

static const char * str_number_type(enum number_type type) {
    switch (type) {
        case DEFICIENT: return "DEFICIENT";
        case PERFECT: return "PERFECT";
        case ABUNDANT: return "ABUNDANT";
    }
    fprintf(stderr, "bad enum value: %d\n", type);
    exit(EXIT_FAILURE);
}

static enum number_type get_number_type(number_t x) {
    number_t s = sum_of_proper_divisors(x);
    if (s < x) return DEFICIENT;
    if (s > x) return ABUNDANT;
    return PERFECT;
}

/**
 * @return 1 if x is a perfect number
 */
static int is_perfect_number(number_t x) {
    return PERFECT == get_number_type(x) ? 1 : 0;
}

static void test(void) {
    Describe("is_perfect_number(x)", do {
        It("should return 1 when x is 28", Assert(is_perfect_number(28)));
        It("should return 0 when x is 12", Assert(!is_perfect_number(12)));
    } while (0));
    Describe("get_number_type(x)", do {
        It("should return ABUNDANT when x is 12",
            Assert(ABUNDANT == get_number_type(12)));
        It("should not be ABUNDANT when x < 12", do {
            number_t i;
            for (i = 0; i < 12; ++i) {
                Assert(ABUNDANT != get_number_type(i));
            }
        } while (0));
    } while (0));
}

int main(int argc, char ** argv) {
    test();

    // Our goal is to find the sum of all positive integers that _CANNOT_ be
    // written as the sum of two abundant numbers.

    // We are told that all integers greater than 28123 _CAN_ be written as the
    // sum of two abundant numbers. Thus our search space, for numbers that
    // _CANNOT_ be written as the sum of two abundant numbers is integers 1 to
    // 28123.

    // The strategy is to first obtain a list of abundant numbers (A). We only
    // need to search numbers from 12 to 28123-12, because 1) 12 is the smallest
    // abundant number (we are told), and 2) another abundant number larger than
    // 28123-12 would sum with 12 to get a number larger than 28123, and those
    // are numbers outside our search space.

    unsigned long long * A;
    unsigned long long n;
    unsigned long long i;

    A = calloc(28124, sizeof(unsigned long long));
    n = 0;
    for (i = 0; i < 28124; ++i) {
        if (ABUNDANT == get_number_type(i)) {
            A[n++] = i;
        }
    }
    printf("There are %llu abundant numbers\n", n);

    // Next we create list of booleans long enough for all our candidate
    // numbers. Initialise all booleans to false. Call this list B.

    unsigned char * B;
    B = calloc(28124, sizeof(unsigned char));

    // Then for each combination (i,j) of values A[i] and A[j], we compute their
    // sum and mark B[A[i]+A[j]] as true, if their sums are within the range.

    unsigned long long j, k;
    unsigned long long m = 0;
    for (i=0; i<n; ++i) {
        for (j=i; j<n; ++j) {
            //printf("i=%llu j=%llu A[i]=%llu A[j]=%llu\n",i,j,A[i],A[j]);
            k = A[i] + A[j];
            if (k < 28124) {
                if (!B[k]) {
                    B[k] = (unsigned char)0x01;
                    m += 1;
                    //printf("i=%llu m=%llu\n", i, m);
                    //printf("%llu: %llu is the sum of %llu and %llu\n", m, k, A[i], A[j]);
                }
            }
        }
    }
    printf("Eliminated %llu numbers\n", m);

    // Next we scan through B. For every false we find, the index to that false
    // is a number that cannot be written as the sum of two abundant numbers.

    unsigned long long sum = 0;
    for (i = 0; i < 28124; ++i) {
        if (!B[i]) {
            sum += i;
            //printf("i = %llu  sum=%llu\n", i, sum);
        }
    }
    printf("sum is %llu\n", sum);

    return 0;
}
