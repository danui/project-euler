package com.euler;

import java.math.BigInteger;
import java.util.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class PrimeFactorsTest {

    @Test
    public void testTwo() {
        PrimeFactors factors = PrimeFactors.factorize(2L);
        assertEquals(1, factors.getList().size());
        assertEquals(Long.valueOf(2L), factors.getList().get(0));
        assertEquals(
            Long.valueOf(1),
            factors.getMap().get(Long.valueOf(2L)));
    }

    @Test
    public void testPrimeFactors() {
        Map<Long,Long> expected = new HashMap<>();
        expected.put(5L, 3L);
        expected.put(2L, 11L);
        expected.put(19L, 1L);
        expected.put(13L, 2L);

        long number = 1;
        for (Map.Entry<Long,Long> entry : expected.entrySet()) {
            for (Long i = 0L; i < entry.getValue(); ++i) {
                number *= entry.getKey();
            }
        }
        // System.out.println("DEBUG number is " + number);

        PrimeFactors factors = PrimeFactors.factorize(number);
        assertEquals(number, factors.getNumber());
        for (Long prime : expected.keySet()) {
            assertTrue(factors.getPrimes().contains(prime));
        }
        for (Long prime : factors.getPrimes()) {
            assertTrue(expected.keySet().contains(prime));
        }
        for (Long prime : factors.getPrimes()) {
            assertEquals(
                expected.get(prime),
                factors.getMap().get(prime));
        }
        // System.out.println("DEBUG factors is " + factors);
    }

    @Test
    public void testMultiply() {
        long valueX = 12345L;
        long valueY = 98765L;
        long valueZ = valueX * valueY;
        PrimeFactors factorsX = PrimeFactors.factorize(valueX);
        PrimeFactors factorsY = PrimeFactors.factorize(valueY);
        PrimeFactors factorsZ = factorsX.multiply(factorsY);
        assertEquals(valueZ, factorsZ.getNumber());
        // System.out.println("DEBUG Z is " + factorsZ);
    }

    @Test
    public void testPow() {
        long valueX = 13L;
        long valueY = 5L;
        long valueZ = 1;
        for (long i = 0; i < valueY; ++i) {
            valueZ *= valueX;
        }
        PrimeFactors factorsX = PrimeFactors.factorize(valueX);
        PrimeFactors factorsZ = factorsX.pow(valueY);
        assertEquals(valueZ, factorsZ.getNumber());
        // System.out.println("DEBUG Z is " + factorsZ);
    }

    @Test
    public void testLoad() {
        List<Long> testCases = new ArrayList<>();
        testCases.add(1L);
        testCases.add(Long.MAX_VALUE);
        for (int i = 0; i < 10; ++i) {
            testCases.add(Long.valueOf((long)(Math.random() * 1000000L)));
        }
        for (Long number : testCases) {
            // System.out.println("DEBUG number is " + number);
            PrimeFactors factors = PrimeFactors.factorize(number);
            String notation = factors.toString();
            PrimeFactors refactored = PrimeFactors.load(notation);
            Long renumbered = refactored.getNumber();
            assertEquals(number, renumbered);
        }
    }

    @Test
    public void testGetBigInteger() {
        PrimeFactors factors = PrimeFactors.factorize(10L);
        factors = factors.pow(2000L);
        BigInteger big = factors.getBigInteger();
        String str = big.toString();
        assertEquals('1', str.charAt(0));
        for (int i = 1; i <= 2000; ++i) {
            assertEquals('0', str.charAt(i));
        }
        // System.out.println("DEBUG factors: " + factors);
    }
}
