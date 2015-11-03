"""
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
"""

N = 600851475143
d = 2
while N > 1:
    while (N % d) != 0 and d < N:
        if d == 2:
            d += 1
        else:
            d += 2
    k = d
    N = N // d
print k


