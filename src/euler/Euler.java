package euler;

public class Euler {

    public static long factorial(long x) {
        if (x < 0) {
            throw new IllegalArgumentException("Bad arg, x: " + x);
        }
        if (x <= 2) {
            return x;
        }
        return x * factorial(x-1);
    }

}
