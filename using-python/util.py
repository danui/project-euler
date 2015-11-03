def n_choose_k(n, k):
    if k > (n//2):
        return n_choose_k(n, n-k)
    x = 1
    y = 1
    for i in xrange(k):
        x *= n-i
        y *= 1+i
    return x // y

def triangle_number(n):
    return n * (n+1) // 2

def sum_of_range(s, t = None):
    if t == None:
        n = s
        b = 0
    else:
        n = t - s + 1
        b = s-1
    return (n * (n+1) // 2) + b * n

def list_of_primes(n):
    if n < 2:
        return []
    marked = [0] * (n+1);
    value = 3
    L = [2]
    while value <= n:
        if marked[value] == 0:
            L.append(value)
            i = value
            while i <= n:
                marked[i] = 1
                i += value
        value += 2
    return L

def extend_list_of_primes(n, P=[]):
    if n < 2:
        return []
    marked = [0] * (n+1)
    for i in P:
        for j in xrange(i, n+1, i):
            marked[j] = 1
    value = 3
    L = [2]
    while value <= n:
        if marked[value] == 0:
            L.append(value)
            i = value
            while i <= n:
                marked[i] = 1
                i += value
        value += 2
    return L

def sum_of_primes(n):
    marked = [0] * (n+1);
    value = 3
    s = 2
    while value <= n:
        if marked[value] == 0:
            s += value
            i = value
            while i <= n:
                marked[i] = 1
                i += value
        value += 2
    return s

def str_is_palindrome(s):
    A = list(s)
    n = len(A)
    for i in xrange(n//2):
        if A[i] != A[n-1-i]:
            return False
    return True

def list_of_prime_factors_v1(n):
    """Returned as a dictionary of { prime factor: count }"""
    L = {}
    k = n
    for i in list_of_primes(n):
        count = 0
        while (k % i) == 0:
            k = k // i
            count += 1
        if count > 0:
            L[i] = count
    return L

def list_of_prime_factors_v2(n):
    """Returned as a dictionary of { prime factor: count }"""
    L = {2:0}
    i = 2
    step = 1
    while n >= i:
        d = n // i;
        r = n - (d * i)
        if r == 0:
            L[i] += 1
            n = d
        else:
            if L[i] == 0:
                L.pop(i)
            i += step
            step = 2
            L[i] = 0
    return L


def list_of_divisors_v1(n):
    """Return [ list of divisors ]"""
    """
    This is a slow algorithm. But it is correct.
    """
    if n == 1:
        return [1]
    if n == 2:
        return [1,2]
    L = {}
    if n > 0:
        L[1] = True
    if n > 1:
        L[n] = True
    for i in list_of_prime_factors(n):
        L[i] = True
        for j in list_of_divisors(n // i):
            L[j] = True
    return L.keys()


def list_of_divisors_v2(n):
    """Return [ list of divisors ]"""
    return list(divisorGen(n))

def prime_factor_generator(n):
    factor = 2
    multiplicity = 0
    step = 1
    while n >= factor:
        d = n // factor
        r = n - (d * factor)
        if r == 0:
            multiplicity += 1
            n = d
        else:
            if multiplicity > 0:
                yield (factor, multiplicity)
            multiplicity = 0
            factor += step
            step = 2
    if multiplicity > 0:
        yield (factor, multiplicity)

def divisorGen(n):
    """
    http://stackoverflow.com/questions/171765/what-is-the-best-way-to-get-all-the-divisors-of-a-number
    """
    factors = list(prime_factor_generator(n))
    nfactors = len(factors)
    if nfactors == 0:
        return
    f = [0] * nfactors
    while True:
        yield reduce(lambda x, y: x*y, [factors[x][0]**f[x] for x in range(nfactors)], 1)
        i = 0
        while True:
            f[i] += 1
            if f[i] <= factors[i][1]:
                break
            f[i] = 0
            i += 1
            if i >= nfactors:
                return



def num_divisors_v1(n):
    if n == 1:
        return 1
    C = {}
    i = 2
    while n >= i:
        if (n%i) == 0:
            n = n // i
            if i in C:
                C[i] += 1
            else:
                C[i] = 1
        else:
            i += 1
    """
    C contains prime factors and their counts.  According to the link
    below we can compute the number of divisors as follows.

    http://mathforum.org/library/drmath/view/55843.html
    """
    x = 1
    for i in C:
        x *= C[i]+1
    return x

def num_divisors_v2(n):
    C = list_of_prime_factors(n)
    x = 1
    for i in C:
        x *= C[i]+1
    return x

"""
Selection of Algorithms
=======================
"""
num_divisors = num_divisors_v2
list_of_prime_factors = list_of_prime_factors_v2
list_of_divisors = list_of_divisors_v2
