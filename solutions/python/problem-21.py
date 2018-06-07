"""
Let d(n) be defined as the sum of proper divisors of n (numbers less
than n which divide evenly into n).

If d(a) = b and d(b) = a, where a != b, then a and b are an amicable
pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20,
22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284
are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
"""
import util

def gen_fn():
    known = {}
    def fn(n):
        if n == 0:
            return 0
        elif n == 1:
            return 0
        elif n == 2:
            return 1
        elif not n in known:
            L = util.list_of_divisors(n)
            L.sort()
            L.pop()
            known[n] = sum(L)
        return known[n]
    return fn

sum_of_pd = gen_fn()

def amicable_generator(limit):
    for a in xrange(2, limit):
        da = b = sum_of_pd(a)
        if a >= b:
            continue
        db = sum_of_pd(b)
        if da == b and db == a and b != a:
            yield (a,b)

n = 0
for i in amicable_generator(10000):
    print i, "->", sum(i)
    n += sum(i)
print n
