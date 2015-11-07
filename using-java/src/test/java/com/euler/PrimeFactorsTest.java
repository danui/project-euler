package com.euler;

import java.util.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class PrimeFactorsTest {

    @Test
    public void testTwo() {
        PrimeFactors factors = new PrimeFactors(2L);
        assertEquals(1, factors.getList().size());
        assertEquals(Long.valueOf(2L), factors.getList().get(0));
        assertEquals(
            Long.valueOf(1),
            factors.getMap().get(Long.valueOf(2L)));
    }

    @Test
    public void testPrimeFactor() {
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
        System.out.println("number is " + number);

        PrimeFactors factors = new PrimeFactors(number);
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
        System.out.println("factors is " + factors);
    }

}
