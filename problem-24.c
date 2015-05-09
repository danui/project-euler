/*

Lexicographic permutations
Problem 24

A permutation is an ordered arrangement of objects. For example, 3124 is one
possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are
listed numerically or alphabetically, we call it lexicographic order. The
lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5,
6, 7, 8 and 9?

*/

#include <stdio.h>

typedef unsigned long long llu;

llu factorial(llu n) {
    llu result = 1;
    while (n > 0) {
        result *= n;
        n -= 1;
    }
    return result;
}

void reasoning(void) {
    llu fact9 = factorial(9);
    printf("0 will be first digit for 9! times.\n");
    printf("9! is %llu\n", fact9);
    printf("1 will be first digit for 9! times after 0.\n");
    printf("9! * 2 is %llu\n", 2*fact9);
    printf("2 will be first digit for 9! times after 1.\n");
    printf("9! * 3 is %llu\n", 3*fact9);
    printf("This is greater than 1 million, therefore the first digit is 3.\n");
    llu target = 1000000 - 2*fact9;
    printf("Offset into the 3 permutations is %llu\n", target);
    printf("This is our new target.\n");

    llu fact8 = factorial(8);
    printf("8! is %llu\n", fact8);
    printf("%llu / %llu is %llu\n", target, fact8, target/fact8);
    printf("Therefore we can skip the 6 digits, 0, 1, 2, 4, 5, 6\n");
    printf("The second digit is 7.\n");
    target -= 6*fact8;
    printf("Number is 37........ and target is %llu\n", target);

    llu fact7 = factorial(7);
    printf("7! is %llu\n", fact7);
    printf("%llu / %llu is %llu\n", target, fact7, target/fact7);
    printf("Therefore we can skip the 6 digits, 0, 1, 2, 4, 5, 6\n");
    printf("The third digit is 8.\n");
    target -= 6*fact7;
    printf("Number is 378....... and target is %llu\n", target);

}

void solver(void) {
    llu fact;
    int in_set[10] = {1,1,1,1,1,1,1,1,1,1};
    int digits[10] = {
        -1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1
    };
    llu i, k, nskip, target;
    llu remaining = 10; // in set
    target = 1000000-1;
    k = 0;
    while (remaining > 0) {
        fact = factorial(remaining - 1);
        nskip = target / fact;
        printf("target: %llu, remaining: %llu, fact: %llu, nskip: %llu\n", target, remaining, fact, nskip);
        target -= nskip * fact;
        for (i = 0; i < 10; ++i) {
            if (in_set[i]) {
                if (nskip > 0) {
                    nskip -= 1;
                } else {
                    digits[k++] = i;
                    in_set[i] = 0;
                    remaining -= 1;
                    //printf("digit %llu\n", i);
                    break;
                }
            }
        }
    }
    printf("ans: ");
    for (i=0; i<10; ++i)
        printf("%d", digits[i]);
    printf("\n");
}

int main(void) {
    reasoning();
    solver();
    return 0;
}
