"""
The sum of the squares of the first ten natural numbers is,

1**2 + 2**2 + ... + 10**2 = 385

The square of the sum of the first ten natural numbers is,

(1 + 2 + ... + 10)**2 = 55**2 = 3025

Hence the difference between the sum of the squares of the first ten
natural numbers and the square of the sum is 3025 385 = 2640.

Find the difference between the sum of the squares of the first one
hundred natural numbers and the square of the sum.
"""

def f(n):
    return (n+1)*n//2



def g(n):
    """
    = 1
    + 2 + 2
    + 3 + 3 + 3
    + 4 + 4 + 4 + 4
    + 5 + 5 + 5 + 5 + 5
    + ...
    + n + n + n + n + n + ... + n

    = f(n) * n - f(n-1) - f(n-2) - ... - f(1)

    = f(n) * n - (n-1)*1 - (n-2)*2

    = (n+1)//2 -

    """
    m = f(n) * n
    while (n-1) >= 1:
        m -= f(n-1)
        n -= 1
    return m

def g_better(n):
    return n * (n+1) * (2*n+1) // 6

def h(n):
    return f(n)**2 - g_better(n)

print "g:", g(10)
print "g_better:", g_better(10)

print "h 10:", h(10)
print "h 100:", h(100)
