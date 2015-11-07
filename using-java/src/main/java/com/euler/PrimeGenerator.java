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

    private final long maxSieveLimit;
    private final ArrayList<Long> primes = new ArrayList<>();
    private final Set<Long> sieve = new HashSet<>();
    private long sieveLimit = 2;
    private long nextOddNumber = 3;

    public PrimeGenerator() {
        this(Long.MAX_VALUE);
    }

    /**
     * @param upto Extend sieve only up to this value.
     */
    public PrimeGenerator(long upto) {
        maxSieveLimit = upto;
        primes.add(Long.valueOf(2L));
    }

    @Override
    public Iterator<Long> iterator() {
        return new IteratorImpl();
    }

    private class IteratorImpl implements Iterator<Long> {
        private int idx = 0;
        private Long nextPrime = null;
        @Override
        public boolean hasNext() {
            nextPrime = getPrime(idx);
            return nextPrime != null;
        }
        @Override
        public Long next() {
            Long result;
            if (nextPrime == null) {
                result = getPrime(idx);
            } else {
                result = nextPrime;
                nextPrime = null;
            }
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
     *
     * @return Prime at idx, or null if that is not possible
     */
    public Long getPrime(int idx) {
        while (idx >= primes.size()) {
            if (!canExtendSieve()) {
                return null;
            }
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

    private boolean canExtendSieve() {
        return sieveLimit < maxSieveLimit;
    }

    private void extendSieve() {
        long extendedLimit;
        long maxExtend = maxSieveLimit - sieveLimit;
        if (maxExtend > sieveLimit) {
            extendedLimit = sieveLimit * 2;
        } else {
            extendedLimit = maxSieveLimit;
        }
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