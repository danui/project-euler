package com.euler;

import java.util.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class PrimeGeneratorTest {

    @Test
    public void testIndependentIterators() {
        PrimeGenerator gen = new PrimeGenerator();
        Iterator<Long> iterA = gen.iterator();
        Iterator<Long> iterB = gen.iterator();
        for (int i = 0; i < 20; ++i) {
            Long p = iterA.next();
            Long q = iterB.next();
            assertEquals(p, q);
            if (false) {
                System.out.format(
                    "i=%d prime=%d sieveLimit=%d numPrimes=%d%n",
                    i, p, gen.getSieveLimit(), gen.getNumPrimes());
            }
        }
    }

    @Test
    public void testForLoop() {
        StringBuilder sb = new StringBuilder();
        int n = 0;
        for (Long prime : new PrimeGenerator()) {
            if (n == 5) {
                break;
            }
            if (n > 0) {
                sb.append(",");
            }
            sb.append(prime.toString());
            n += 1;
        }
        assertEquals("2,3,5,7,11", sb.toString());
    }

    @Test
    public void testLimits() {
        StringBuilder sb = new StringBuilder();
        int n = 0;
        PrimeGenerator gen = new PrimeGenerator(13L);
        for (Long prime : gen) {
            if (false) {
                System.out.format(
                    "n=%d prime=%d sieveLimit=%d numPrimes=%d%n",
                    n, prime, gen.getSieveLimit(), gen.getNumPrimes());
            }
            if (n > 0) {
                sb.append(",");
            }
            sb.append(prime.toString());
            n += 1;
        }
        assertEquals("2,3,5,7,11,13", sb.toString());
    }

}
