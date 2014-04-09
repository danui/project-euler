/**
 * Problem 103
 *
 * Let S(A) represent the sum of elements in set A of size n.  We shall
 * call it a special sum set if for any two non-empty disjoint subsets,
 * B and C, the following properties are true:
 *
 *   i) S(B) != S(C); that is, sums of subsets cannot be equal.
 *  ii) If B contains more elements than C then S(B) > S(C).
 *
 * If S(A) is minimised for a given n, we shall call it an optimum
 * special sum set.  The first five optimum special sum sets are given
 * below.
 *
 *      n = 1: {1}
 *      n = 2: {1, 2}
 *      n = 3: {2, 3, 4}
 *      n = 4: {3, 5, 6, 7}
 *      n = 5: {6, 9, 11, 12, 13}
 *
 * It _seems_ that for a given optimum set, A = {a_1, a_2, ..., a_n},
 * the next optimum set is of the form B = {b, a_1+b, a2+b, ... a_n+b},
 * where b is the "middle" element on the previous row.
 *
 * By applying this "rule" we would expect the optimum set for n = 6 to
 * be A = {11, 17, 20, 22, 23, 24}, with S(A) = 117.  However, this is
 * not the optimum set, as we have merely applied an algorithm to
 * provide a near optimum set.  The optimum set for n = 6 is A = {11,
 * 18, 19, 20, 22, 25}, with S(A) = 115 and corresponding set string:
 * 111819202225.
 *
 * Given that A is an optimum special sum set for n = 7, find its set
 * string.
 *
 * NOTE: This problem is related to problems 105 and 106.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Test if set A satisfies conditions (i) and (ii) above.  The general
 * idea is to try to break the conditions individually since the
 * conditions apply to _any_ pair of non-empty disjoint subsets.
 *
 * Rule (i) is broken by trying to even out the sums.
 *
 * Rule (ii) is broken by giving the smallests numbers to B such that B
 * has got more elements than C.
 */
int satisfies(int A, int n)
{
    int nB = 0;
    int nC = 0;
    int SB = 0;
    int SC = 0;
    int i;

    /* TODO: ? */
    return 0;
}

int main(void)
{
    return 0;
}
