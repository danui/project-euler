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
 * Test if set A satisfies properties (i) and (ii) above.  The general
 * idea is to try to voilate the properties individually since the
 * properties apply to _any_ pair of non-empty disjoint subsets.
 *
 * Property (i) is broken by trying to even out the sums.
 *
 * Property (ii) is broken by giving the smallests numbers to B such
 * that B has got more elements than C.
 *
 * @param A,n [in] A _sorted_ array of n integers.
 *
 * @return 1 if A satisfies the conditions required for both properties.
 */
int satisfies(int *A, int n)
{
    int nB, SB;
    int nC, SC;
    int i;

    /* Breaking (ii).  (note A must be sorted)  */
    SB = 0;
    SC = 0;
    nB = n/2 + 1;
    nC = n - nB;
    if (nC > 0) {
        for (i=0; i < nB; ++i)
            SB += A[i];
        for (i=nB; i < n; ++i)
            SC += A[i];
        if (SB <= SC)
            return 0;
    }

    /* Breaking (i). */

    /* Firstly, no two elements may be equal otherwise two subsets, each
     * consisting of one of those elements would be equal.
     */
    for (i=1; i < n; ++i)
        if (A[i] == A[i-1])
            return 0;

    /* NOTES:
     *
     *   o If no two elements are equal, then the minimum gap between
     *     consecutive elements in A is 1.
     *
     *    o The lower bound on S(A) is
     *
     *          A[0] * n + (n-1)*(n)/2
     */

    /* TODO:... */

    return 1;
}

int test_satisfies(void)
{
    int A[10];
    int n;

    n = 0;
    A[n++] = 1;
    if (!satisfies(A, n)) return -1;

    n = 0;
    A[n++] = 1;
    A[n++] = 2;
    if (!satisfies(A, n)) return -1;

    n = 0;
    A[n++] = 2;
    A[n++] = 3;
    A[n++] = 4;
    if (!satisfies(A, n)) return -1;

    n = 0;
    A[n++] = 3;
    A[n++] = 5;
    A[n++] = 6;
    A[n++] = 7;
    if (!satisfies(A, n)) return -1;

    n = 0;
    A[n++] = 6;
    A[n++] = 9;
    A[n++] = 11;
    A[n++] = 12;
    A[n++] = 13;
    if (!satisfies(A, n)) return -1;

    /* negative test */
    n = 0;
    A[n++] = 6;
    A[n++] = 9;
    A[n++] = 11;
    A[n++] = 12;
    A[n++] = 130;               /* nB > nC but SB < SC */
    if (satisfies(A, n)) return -1;

    /* negative test */
    n = 0;
    A[n++] = 6;
    A[n++] = 9;
    A[n++] = 11;                /* {11} vs {11} */
    A[n++] = 11;
    A[n++] = 13;
    if (satisfies(A, n)) return -1;

    return 0;
}

int main(void)
{
    if (0 != test_satisfies()) {
        printf("satisfies not working\n");
        exit(EXIT_FAILURE);
    }
    printf("okay\n");
    return 0;
}
