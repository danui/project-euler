package com.euler;

import java.util.*;
import java.util.concurrent.*;

/**
 * Problem 32
 * ==========
 *
 * We shall say that an n-digit number is pandigital if it makes use of all the
 * digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1
 * through 5 pandigital.
 *
 * The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing
 * multiplicand, multiplier, and product is 1 through 9 pandigital.
 *
 * Find the sum of all products whose multiplicand/multiplier/product identity
 * can be written as a 1 through 9 pandigital.
 *
 * HINT: Some products can be obtained in more than one way so be sure to only
 * include it once in your sum.
 *
 * Observations
 * ============
 *
 * Given multiplicand, multiplier, and product...
 *
 *     A x B = C
 *
 * C cannot be more than 5 digits. Otherwise there would be insufficient
 * digits for A and B to form a product that equals C.
 *
 * C cannot be 3 or less digits. Otherwise there would be too many digits
 * for A and B to form a product equal to C.
 */
public class Problem32 implements Problem {

    private final ExecutorService executorService;
    private final BlockingQueue<List<Integer>> permutationQueue;

    public static void main(String[] args) {
        System.out.println("ans: " + new Problem32().call());
    }

    public Problem32() {
        executorService = Executors.newCachedThreadPool();
        permutationQueue = new ArrayBlockingQueue<>(10);
    }

    @Override
    public String call() {
        try {
            return solve();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private String solve() throws InterruptedException {
        executorService.submit(new PermutationTask());
        List<Integer> permutation;
        Long sum = 0L;
        TreeSet<Long> bag = new TreeSet<>();
        while (null != (permutation = permutationQueue.poll(100,
            TimeUnit.MILLISECONDS))) {

            Integer[] ary = permutation.toArray(new Integer[0]);
            for (int c=4; c <= 5; ++c) {
                for (int b=1; b <= 9-c-1; ++b) {
                    int a=9-b-c;
                    Long val = filter(ary, a, b, c);
                    if (val > 0 && !bag.contains(val)) {
                        sum += val;
                        System.out.println(String.format("%s -> %d (sum = %d)",
                            strlist(permutation), val, sum));
                        bag.add(val);
                    }
                }
            }
        }
        executorService.shutdownNow();
        executorService.awaitTermination(100, TimeUnit.MILLISECONDS);
        return sum.toString();
    }

    private long filter(Integer[] ary, int a, int b, int c) {
        int i = 0;
        long multiplicand = 0;
        long multiplier = 0;
        long product = 0;
        for (; i < a; ++i) {
            multiplicand *= 10;
            multiplicand += ary[i];
        }
        for (; i < a+b; ++i) {
            multiplier *= 10;
            multiplier += ary[i];
        }
        for (; i < a+b+c; ++i) {
            product *= 10;
            product += ary[i];
        }
        if (multiplicand * multiplier == product) {
            return product;
        }
        return 0;
    }

    private String strlist(List<Integer> list) {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        boolean first = true;
        for (Integer i : list) {
            if (first) {
                first = false;
            } else {
                sb.append(",");
            }
            sb.append(i);
        }
        sb.append("]");
        return sb.toString();
    }


    private class PermutationTask implements Runnable {
        @Override
        public void run() {
            try {
                start();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        private void start() throws InterruptedException {
            LinkedList<Integer> digits = new LinkedList<>();
            for (Integer i = 1; i <= 9; ++i) {
                digits.addLast(i);
            }
            LinkedList<Integer> sequence = new LinkedList<>();
            permutate(sequence, digits);
        }

        private void permutate(LinkedList<Integer> sequence,
            LinkedList<Integer> digits) throws InterruptedException {

            if (digits.isEmpty()) {
                permutationQueue.put((List)sequence.clone());
                return;
            }
            int n = digits.size();
            for (int i = 0; i < n; ++i) {
                sequence.addLast(digits.removeFirst());
                permutate(sequence, digits);
                digits.addLast(sequence.removeLast());
            }
        }
    }
}
