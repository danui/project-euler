"""
2520 is the smallest number that can be divided by each of the numbers
from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of
the numbers from 1 to 20?
"""

import util

R = {}
for i in xrange(1,21):
    L = util.list_of_prime_factors(i)
    for j in L:
        if not R.has_key(j):
            R[j] = L[j]
        elif R[j] < L[j]:
            R[j] = L[j]
x = 1
for i in R:
    x *= i ** R[i]
print x

# Manual
x = 1
for i in [1,2,3,4,5,6,7,11,13,17,19]:
    x *= i
print x
