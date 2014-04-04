"""
A Pythagorean triplet is a set of three natural numbers, a b c, for
which,

a**2 + b**2 = c**2

For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
"""

def f(a,b,c):
    return (a**2 + b**2) == c**2

def g(a,b,c, TARGET):
    return (a+b+c) == TARGET

for a in xrange(1,1001):
    for b in xrange(1,1001-a):
        c = 1000-a-b
        fv = f(a,b,c)
        print (a,b,c), fv
        if fv:
            print "FOUND, abc:", (a*b*c)
            exit()
