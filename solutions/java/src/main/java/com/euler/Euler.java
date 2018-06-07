package com.euler;

import java.util.List;
import java.util.ArrayList;
import java.util.BitSet;

public class Euler {

    /**
     * @return A list of prime numbers up to n
     */
    public static List<Integer> getPrimesUpTo(int n) {
        List<Integer> list = new ArrayList<Integer>();
        // There are no prime numbers under 2. Note that 1 is not prime.
        if (n < 2) {
            return list;
        }
        // 2 is in the list, for all values of n >= 2.
        list.add(new Integer(2));
        BitSet marked = new BitSet();
        for (int k = 3; k <= n; k += 2) {
            if (!marked.get(k)) {
                list.add(new Integer(k));
                for (int i = k; i <= n; i += k) {
                    marked.set(i);
                }
            }
        }
        return list;
    }

    public static List<Integer> getPrimesUnder(int n) {
        return getPrimesUpTo(n-1);
    }
}
