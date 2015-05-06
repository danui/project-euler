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
#include "walltime.h"

/**
 * @return 1 if divisor is a proper divisor of subject.
 */
static int is_proper_divisor(
    unsigned long long subject,
    unsigned long long divisor)
{
    return (subject % divisor) == 0 ? 1:0;
}

static unsigned long long sum_of_proper_divisors(unsigned long long x) {
    unsigned long long i;
    unsigned long long j;
    unsigned long long sum;
    unsigned long long upper;

    /* zero is not a perfect number */
    if (x == 0) return 0;

    upper = x;
    // printf("\n%llu: [1", x);
    sum = 1;
    for (i = 2; i < upper; ++i) {
        // printf("(i=%llu)" ,i);
        j = x / i;
        if (j*i == x) {
            if (i == j) {
                sum += i;
                // printf(",%llu", i);
            } else {
                sum += i + j;
                // printf(",%llu", i);
                // printf(",%llu", j);
            }
            upper = (i+j) >> 1;
        }
        // printf("(upper=%llu)", upper);
    }
    // printf("]\n");
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

static enum number_type get_number_type(unsigned long long x) {
    unsigned long long s = sum_of_proper_divisors(x);
    if (s < x) return DEFICIENT;
    if (s > x) return ABUNDANT;
    return PERFECT;
}

/**
 * @return 1 if x is a perfect number
 */
static int is_perfect_number(unsigned long long x) {
    return PERFECT == get_number_type(x) ? 1 : 0;
}

static void test(void) {
    Describe("is_perfect_number(x)", do {
        It("should return 1 when x is 28", Assert(is_perfect_number(28)));
        It("should return 0 when x is 12", Assert(!is_perfect_number(12)));
    } while (0));
    Describe("sum_of_proper_divisors(x)", do {
        It("should return 28 when x is 28",
            Assert(28 == sum_of_proper_divisors(28)));
        It("should return 16 when x is 12",
            Assert(16 == sum_of_proper_divisors(12)));
        It("should return 3 when x is 4",
            Assert(3 == sum_of_proper_divisors(4)));
        // 16
        //1, 2, 4, 8 = 15
        It("should return 15 when x is 16",
            Assert(15 == sum_of_proper_divisors(16)));
    } while (0));
    Describe("get_number_type(x)", do {
        It("should return ABUNDANT when x is 12",
            Assert(ABUNDANT == get_number_type(12)));
        It("should not be ABUNDANT when x < 12", do {
            unsigned long long i;
            for (i = 0; i < 12; ++i) {
                Assert(ABUNDANT != get_number_type(i));
            }
        } while (0));
    } while (0));
}

static void solve(void) {
    // Our goal is to find the sum of all positive integers that _CANNOT_ be
    // written as the sum of two abundant numbers.

    // We are told that all integers greater than 28123 _CAN_ be written as the
    // sum of two abundant numbers. Thus our search space, for numbers that
    // _CANNOT_ be written as the sum of two abundant numbers is integers 1 to
    // 28123.

    // The strategy is to first obtain a list of abundant numbers (A). We only
    // need to be concerned with abundant numbers up to 28123 because any
    // abundant number greate than that would lead to a sum greater than 28123,
    // which is outside our search space.

    // We do not know how many abundant numbers there are, so we just provision
    // enough for 28123.

    unsigned long long * A;
    unsigned long long n;
    unsigned long long i;
    A = calloc(28123, sizeof(unsigned long long));
    n = 0;
    for (i = 1; i <= 28123; ++i) {
        if (ABUNDANT == get_number_type(i)) {
            A[n++] = i;
        }
    }
    printf("There are %llu abundant numbers\n", n);

    // Next we create list of booleans long enough for all our candidate
    // numbers. Initialise all booleans to false. Call this list B.

    // Notes:
    //
    // - Allocate 28124 because you need slot B[28123].
    // - Use calloc so everything is false.

    unsigned char * B;
    B = calloc(28124, sizeof(unsigned char));

    // Then for each possible pair of values from A, we compute their sum as k.
    // k is therefore a number that is a sum of two abundant numbers. If k is in
    // the range 0 <= k < 29124, then mark B[k] as true.

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

    // At this point, the index numbers of the false values remaining in B are
    // numbers that cannot be written as the sum of two abundant numbers.
    // Iterate through B and sum up the indices i where B[i] is false.

    unsigned long long sum = 0;
    for (i = 0; i < 28124; ++i) {
        if (!B[i]) {
            sum += i;
            //printf("i = %llu  sum=%llu\n", i, sum);
        }
    }
    printf("sum is %llu\n", sum);
}

int main(int argc, char ** argv) {
    //test();
    unsigned long long t0, t1;
    t0 = walltime_ms();
    solve();
    t1 = walltime_ms();
    printf("milliseconds: %llu\n", t1-t0);
    return 0;
}
