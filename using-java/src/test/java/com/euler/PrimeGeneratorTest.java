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
            System.out.format("i=%d prime=%d sieveLimit=%d numPrimes=%d%n",
                i, p, gen.getSieveLimit(), gen.getNumPrimes());
        }
    }

}
