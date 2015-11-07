package com.euler;

import java.util.*;

public class PrimeFactors {

    private final long number;
    private final TreeMap<Long,Long> map = new TreeMap<>();

    public PrimeFactors(long number) {
        this.number = number;
        Long denominator = 2L;
        while (number > 1) {
            Long exponent = 0L;
            while (number > 1 && 0 == (number % denominator)) {
                number /= denominator;
                exponent += 1;
            }
            if (exponent > 0) {
                map.put(denominator, exponent);
            }
            denominator += 1;
        }
    }

    public long getNumber() {
        return number;
    }

    /**
     * Get list of prime factors.
     *
     * <p> There may be repeats in the list.
     *
     * @return List
     */
    public List<Long> getList() {
        List<Long> result = new ArrayList<>();
        for (Map.Entry<Long,Long> entry : map.entrySet()) {
            Long prime = entry.getKey();
            Long exponent = entry.getValue();
            for (Long i = 0L; i < exponent; ++i) {
                result.add(prime);
            }
        }
        return result;
    }

    /**
     * Get map of prime factors and their exponents.
     *
     * @return Map
     */
    public Map<Long,Long> getMap() {
        return map;
    }

    /**
     * @return List of primes that are factors of number.
     */
    public Set<Long> getPrimes() {
        return map.keySet();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("1");
        for (Map.Entry<Long,Long> entry : map.entrySet()) {
            sb.append("*(")
                .append(entry.getKey())
                .append("^")
                .append(entry.getValue())
                .append(")");
        }
        return sb.toString();
    }
}
