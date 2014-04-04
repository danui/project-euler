"""
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can
see that the 6th prime is 13.

What is the 10001st prime number?
"""

# This uses a growable sieve
def kth_prime(k):
    P = [2]                         # list of primes
    A = [1, 1, 1]                   # seen.
    x = 3                           # current value
    while len(P) < k:
        # If the sieve is too small double its size
        if len(A) < x+1:
            n = len(A)
            A = A + [0]*n
            for y in P:
                j = n//y * y
                while j < len(A):
                    A[j] = 1
                    j += y

        if A[x] == 0:
            j = x
            while j < len(A):
                A[j] = 1
                j += x
            P.append(x)
        x += 2
    return P[k-1]

for k in [6, 100, 10001]:
    print "The %d'th prime is %d" % (k, kth_prime(k))

