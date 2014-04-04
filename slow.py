def list_of_primes_slow(n):
    if n < 2:
        return []
    if n == 2:
        return [2]
    L = [2]
    def is_prime(i):
        for j in L:
            if (i % j) == 0:
                return False
            if j > i//j:
                return True
        return True

    x = 3
    while x <= n:
        if is_prime(x):
            L.append(x)
        x += 2
    return L

def sum_of_primes_slow(n):
    if n < 2:
        return []
    if n == 2:
        return [2]
    L = [2]
    def is_prime(i):
        for j in L:
            if (i % j) == 0:
                return False
            if j > i//j:
                return True
        return True
    m = 2
    x = 3
    while x <= n:
        if is_prime(x):
            L.append(x)
            m += x
        x += 2
    return m
