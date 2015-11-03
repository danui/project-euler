package com.euler;

// Solution posted on page 8.

/*

Lexicographic permutations
Problem 24

A permutation is an ordered arrangement of objects. For example, 3124 is one
possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are
listed numerically or alphabetically, we call it lexicographic order. The
lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5,
6, 7, 8 and 9?

*/

import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.Callable;

public class Problem24 implements Problem, Callable<String> {

    @Override
    public String getName() {
        return "24";
    }

    @Override
    public Callable<String> getTask() {
        return this;
    }

    @Override
    public String call() {
        long t0 = System.currentTimeMillis();
        String result = solve();
        long t1 = System.currentTimeMillis();
        long elapsed = t1 - t0;
        System.out.println("elapsed msec: " + elapsed);
        return result;
    }

    /**
     * Solver
     */
    private String solve() {

        // Observation.
        //
        // Given a set of k digits, the first factorial(k-1) permutations will
        // begin with the smallest digit in that set.
        //

        // Let 'digits' be a list of candidate digits.
        List<Integer> digits = new ArrayList<Integer>();
        for (int i = 0; i <= 9; ++i) {
            digits.add(new Integer(i));
        }

        // Let 'solution' be a list of digits in the order of our solution.
        List<Integer> solution = new ArrayList<Integer>();

        // We need to track the number of permutations we have "seen".
        int numSeen = 0;

        // And we need a target permutation.
        int targetPermutation = 1000000;

        // Since we want the targetPermutation'th, the targetSeen is that -1.
        int targetSeen = targetPermutation - 1;

        // How long should we run for? Put it this way. A solution permutation
        // must contain all of the digits. Thus the following loop must execute
        // until the list of digits is empty.
        //
        // While there are digits...
        while (!digits.isEmpty()) {
            int k = digits.size();
            int f = factorial(k-1);
            int gap = targetSeen - numSeen;
            int i = gap / f;
            // System.out.println(String.format(
            //     "k: %d, f: %d, gap: %d, i: %d, numSeen: %d",
            //     k, f, gap, i, numSeen));
            solution.add(digits.remove(i));
            numSeen += i * f;
        }

        StringBuilder sb = new StringBuilder();
        for (Integer i : solution) {
            sb.append(i);
        }
        System.out.println("ans: " + sb.toString());
        return sb.toString();
    }

    private int factorial(int n) {
        // Note: factorial 0 is 1.
        if (n < 0) {
            throw new IllegalArgumentException("Bad arg, n is " + n);
        }
        int result = 1;
        for (int i = 1; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
}
