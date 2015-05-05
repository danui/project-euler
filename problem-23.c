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

typedef uint64_t number_t;

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
            upper = j;
        }
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

/**
 * @param x   Can x be written as sum of two abundant numbers
 * @param L   Array of abundant numbers.
 * @param n   Number of abundant numbers in L.
 */
static int can_be_written(number_t x, number_t * L, number_t n) {
    number_t i, j;
    for (i = 0; L[i] < x; ++i) {
        for (j=i; L[j] < x; ++j) {
            if (L[i] + L[j] == x) {
                //printf("%u + %u -> %u\n", L[i], L[j], x);
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char ** argv) {
    test();
    number_t limit = 28124;
    number_t i, n;
    number_t * abnos;

    if (NULL == (abnos = malloc(sizeof(*abnos) * limit))) {
        perror("malloc failed");
    }
    n = 0;
    for (i = 0; i < limit; ++i) {
        if (ABUNDANT == get_number_type(i)) {
            abnos[n] = i;
            n += 1;
        }
    }
    number_t sum = 0;
    for (i = 0; i < limit; ++i) {
        if (!can_be_written(i, abnos, n)) {
            printf("Number %llu cannot be written as sum of two abundant numbers\n", (unsigned long long)i);
            sum += i;
        }
    }
    printf("%llu\n", (unsigned long long)sum);


    return 0;
}
