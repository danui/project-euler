package com.euler;
/*

Starting with the number 1 and moving to the right in a clockwise direction a 5
by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed
in the same way?

*/

import static org.junit.Assert.*;

public class Problem28 implements Problem {

    @Override
    public String call() {
        assertEquals(101, getSumOfDiagonals(5));
        return Long.valueOf(getSumOfDiagonals(1001)).toString();
    }

    private long getSumOfDiagonals(long dimension) {
        long sum = 1;
        long cursor = 1;
        for (long n = 3; n <= dimension; n += 2) {
            long step = n - 1;
            for (int i = 0; i < 4; ++i) {
                cursor += step;
                sum += cursor;
            }
        }
        return sum;
    }

}
