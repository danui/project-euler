package com.euler;

/*

Quadratic primes
Problem 27

Euler discovered the remarkable quadratic formula:

    n² + n + 41

It turns out that the formula will produce 40 primes for the consecutive values
n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible
by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.

The incredible formula  n² − 79n + 1601 was discovered, which produces 80 primes
for the consecutive values n = 0 to 79. The product of the coefficients, −79 and
1601, is −126479.

Considering quadratics of the form:

    n² + an + b, where |a| < 1000 and |b| < 1000

where |n| is the modulus/absolute value of n

    e.g. |11| = 11 and |−4| = 4

Find the product of the coefficients, a and b, for the quadratic expression that
produces the maximum number of primes for consecutive values of n, starting with
n = 0.

*/

import java.util.*;
import java.util.concurrent.Callable;
import static org.junit.Assert.*;

public class Problem27 implements Problem {

    private final Set<Integer> primes = new HashSet<>();

    @Override
    public String call() {
        // Calcualte the maximum value of quadratic formula. This occurs when n,
        // a, and b are at maximum.
        int MAX_N = 1000;
        int MAX_A = 999;
        int MAX_B = 999;
        int MAX_VAL = new Coefficients(MAX_A, MAX_B).getQuadratic(MAX_N);
        //System.out.format("MAX_VAL is %d%n", MAX_VAL);

        // Load 'primes' with primes.
        for (Integer prime : Euler.getPrimesUpTo(MAX_VAL)) {
            primes.add(prime);
        }

        // Sanity check for isPrime
        assertTrue(isPrime(41));
        assertFalse(isPrime(69));

        // Sanity check for Coefficients
        assertEquals(40, new Coefficients(1,41).getNumConsecutive());
        assertEquals(80, new Coefficients(-79,1601).getNumConsecutive());
        assertEquals(-126479, new Coefficients(-79,1601).getProduct());

        Coefficients best = null;
        for (int a = -999; a < 1000; ++a) {
            for (int b = -999; b < 1000; ++b) {
                Coefficients curr = new Coefficients(a, b);
                if (best == null ||
                    best.getNumConsecutive() < curr.getNumConsecutive()) {

                    best = curr;
                    System.out.format("New BEST is a=%d, b=%d consec=%d%n",
                        best.getA(),
                        best.getB(),
                        best.getNumConsecutive());
                }
            }
        }

        return String.format("%d", best.getProduct());
    }

    private boolean isPrime(int x) {
        return primes.contains(Integer.valueOf(x));
    }

    private class Coefficients {
        private final int a;
        private final int b;
        private Integer numConsecutive = null;
        public Coefficients(int a, int b) {
            this.a = a;
            this.b = b;
        }
        public int getA() {
            return a;
        }
        public int getB() {
            return b;
        }
        public int getProduct() {
            return a * b;
        }
        public int getNumConsecutive() {
            if (numConsecutive == null) {
                int n = 0;
                while (isPrime(getQuadratic(n))) {
                    n += 1;
                }
                //System.out.format("%d is not prime%n", getQuadratic(n));
                numConsecutive = n;
            }
            return numConsecutive;
        }
        public int getQuadratic(int n) {
            return n*n + a*n + b;
        }
    }

}
