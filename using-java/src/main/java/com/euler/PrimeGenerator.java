package com.euler;

import java.util.*;

/**
 * Prime Number Generator
 *
 * Usage Example
 *
 * Iterable<Long> g = new PrimeGenerator();
 * for (Long i : g) {
 *     System.out.format("%d is a prime number%n", i);
 * }
 */
public class PrimeGenerator implements Iterable<Long> {

    private final ArrayList<Long> primes = new ArrayList<>();
    private final Set<Long> sieve = new HashSet<>();
    private long sieveLimit = 2;
    private long nextOddNumber = 3;

    public PrimeGenerator() {
        primes.add(Long.valueOf(2L));
    }

    @Override
    public Iterator<Long> iterator() {
        return new IteratorImpl();
    }

    private class IteratorImpl implements Iterator<Long> {
        private int idx = 0;
        @Override
        public boolean hasNext() {

            // There's always a next prime number
            return true;
        }
        @Override
        public Long next() {
            Long result = getPrime(idx);
            idx += 1;
            return result;
        }
        @Override
        public void remove() {
            throw new UnsupportedOperationException(
                "Cannot remove from a generator");
        }
    }

    /**
     * The normal way to use this is through the iterator. This is intended for
     * testing, but could also be useful.
     */
    public Long getPrime(int idx) {
        while (idx >= primes.size()) {
            extendSieve();
        }
        return primes.get(idx);
    }

    public long getSieveLimit() {
        return sieveLimit;
    }

    public int getNumPrimes() {
        return primes.size();
    }

    private void extendSieve() {
        long extendedLimit = sieveLimit * 2;
        for (Long prime : primes) {
            if (prime == 2L) {
                continue;
            }
            long startPosition = (sieveLimit / prime) * prime;
            for (Long multiple = startPosition; multiple <= extendedLimit;
                multiple += prime) {

                sieve.add(multiple);
            }
        }
        sieveLimit = extendedLimit;
        for (Long candidate = nextOddNumber; candidate <= sieveLimit;
            candidate += 2) {

            if (sieve.contains(candidate)) {
                continue;
            }
            primes.add(candidate);
            for (Long multiple = candidate; multiple <= sieveLimit;
                multiple += candidate) {

                sieve.add(multiple);
            }
        }
    }
}