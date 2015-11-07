package com.euler;
/*

Surprisingly there are only three numbers that can be written as the sum of
fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers
of their digits.

*/

import java.math.*;
import java.util.*;
import static org.junit.Assert.*;

public class Problem30 implements Problem {

    @Override
    public String call() {
        assertEquals(19316L, search(4L));
        return Long.valueOf(search(5L)).toString();
    }

    private long search(long exponent) {
        long sum = 0;
        long[] powers = getPowers(exponent);
        long searchLimit = getSearchLimit(powers);
        // System.out.format("DEBUG Search Limit is %d%n", searchLimit);
        for (long k = 2; k < searchLimit; ++k) {
            int[] digits = getDigits(k);
            long sop = sumOfPowersOfDigits(digits, powers);
            if (k == sop) {
                sum += k;
                // System.out.format("DEBUG Found %d%n", k);
            }
        }
        return sum;
    }

    private long[] getPowers(long exponent) {
        long[] powers = new long[10];
        for (int i = 0; i < 10; ++i) {
            powers[i] = i;
            for (long j = 0; j < exponent-1; ++j) {
                powers[i] *= i;
            }
            //System.out.format("DEBUG powers[%d] = %d%n", i, powers[i]);
        }
        return powers;
    }

    private long getSearchLimit(long[] powers) {
        long k = powers[9];
        long result = 10;
        while (k+powers[9] > result) {
            // System.out.format("DEBUG result=%d k=%d%n", result, k);
            result *= 10;
            k += powers[9];
        }
        // System.out.format("DEBUG result=%d k=%d%n", result, k);
        return result;
    }

    private int[] getDigits(long number) {
        int count = 0;
        for (long k = number; k > 0; k /= 10) {
            count += 1;
        }
        int[] result = new int[count];
        count = 0;
        for (long k = number; k > 0; k /= 10) {
            result[count] = (int)(k % 10);
            count += 1;
        }
        return result;
    }

    private long sumOfPowersOfDigits(int[] digits, long[] powers) {
        long sum = 0;
        for (int i = 0; i < digits.length; ++i) {
            sum += powers[digits[i]];
        }
        return sum;
    }
}
