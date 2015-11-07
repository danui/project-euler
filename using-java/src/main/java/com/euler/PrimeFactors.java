package com.euler;

import java.math.BigInteger;
import java.util.*;

public class PrimeFactors {

    private static PrimeGenerator primeGen = new PrimeGenerator();

    /**
     * Load from strings of this form
     *
     *     "1*(2^10)";
     *     "1*(13^5)*(17^1)"
     *
     */
    public static PrimeFactors load(String notation) {
        // System.out.println("DEBUG notation is " + notation);
        TreeMap<Long,Long> map = new TreeMap<>();
        String[] parts = notation.split("[*]");
        for (int i = 1; i < parts.length; ++i) {
            String part = parts[i];
            // System.out.println("DEBUG part is " + part);
            part = part.substring(1, part.length() - 1);
            String[] kv = part.split("[\\^]");
            // System.out.format("DEBUG kv[] is [%s, %s]%n", kv[0], kv[1]);
            map.put(Long.valueOf(kv[0]), Long.valueOf(kv[1]));
        }
        return new PrimeFactors(map);
    }

    public static PrimeFactors factorize(long number) {
        TreeMap<Long,Long> map = new TreeMap<>();
        Iterator<Long> primeIter = primeGen.iterator();
        while (number > 1) {
            Long denominator = primeIter.next();
            Long exponent = 0L;
            while (number > 1 && 0 == (number % denominator)) {
                number /= denominator;
                exponent += 1;
            }
            if (exponent > 0) {
                map.put(denominator, exponent);
            }
        }
        return new PrimeFactors(map);
    }

    public static PrimeFactors valueOf(long number) {
        return factorize(number);
    }

    public static PrimeFactors init(Map<Long,Long> map) {
        // Assumes that map keys are prime numbers.
        return new PrimeFactors(copyMap(map));
    }

    private final SortedMap<Long,Long> map;
    private String stringNotation = null;

    private PrimeFactors(TreeMap<Long,Long> map) {
        this.map = Collections.unmodifiableSortedMap(map);
    }

    public long getNumber() {
        long number = 1;
        for (Map.Entry<Long,Long> entry : map.entrySet()) {
            for (Long i = 0L; i < entry.getValue(); ++i) {
                number *= entry.getKey();
            }
        }
        return number;
    }

    public BigInteger getBigInteger() {
        BigInteger result = BigInteger.ONE;
        for (Map.Entry<Long,Long> entry : map.entrySet()) {
            BigInteger prime = BigInteger.valueOf(entry.getKey());
            for (Long i = 0L; i < entry.getValue(); ++i) {
                result = result.multiply(prime);
            }
        }
        return result;
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
        if (stringNotation == null) {
            StringBuilder sb = new StringBuilder();
            sb.append("1");
            for (Map.Entry<Long,Long> entry : map.entrySet()) {
                sb.append("*(")
                    .append(entry.getKey())
                    .append("^")
                    .append(entry.getValue())
                    .append(")");
            }
            stringNotation = sb.toString();
        }
        return stringNotation;
    }

    @Override
    public boolean equals(Object otherObject) {
        if (otherObject == null) return false;
        if (!(otherObject instanceof PrimeFactors)) return false;
        PrimeFactors other = (PrimeFactors)otherObject;
        return equalMaps(map, other.getMap());
    }

    @Override
    public int hashCode() {
        return toString().hashCode();
    }

    /**
     * @return A new PrimeFactors that is a product of this PrimeFactors and
     *     the 'other' PrimeFactors.
     */
    public PrimeFactors multiply(PrimeFactors other) {
        TreeMap<Long,Long> result = copyMap(map);
        for (Map.Entry<Long,Long> entry: other.getMap().entrySet()) {
            if (result.containsKey(entry.getKey())) {
                result.put(entry.getKey(),
                    result.get(entry.getKey()) + entry.getValue());
            } else {
                result.put(entry.getKey(), entry.getValue());
            }
        }
        return new PrimeFactors(result);
    }

    /**
     * @return A new PrimeFactors that is this PrimeFactors raised to the
     *     'exponent'.
     */
    public PrimeFactors pow(long exponent) {
        TreeMap<Long,Long> result = copyMap(map);
        for (Map.Entry<Long,Long> entry: result.entrySet()) {
            result.put(entry.getKey(),
                result.get(entry.getKey()) + exponent - 1);
        }
        return new PrimeFactors(result);
    }

    private static TreeMap<Long,Long> copyMap(Map<Long,Long> src) {
        TreeMap<Long,Long> result = new TreeMap<>();
        for (Map.Entry<Long,Long> entry : src.entrySet()) {
            result.put(entry.getKey(), entry.getValue());
        }
        return result;
    }

    private static boolean equalMaps(Map<Long,Long> x, Map<Long,Long> y) {
        for (Map.Entry<Long,Long> entry : x.entrySet()) {
            if (!entry.getValue().equals(y.get(entry.getKey()))) return false;
        }
        for (Map.Entry<Long,Long> entry : y.entrySet()) {
            if (!entry.getValue().equals(x.get(entry.getKey()))) return false;
        }
        return true;
    }
}
