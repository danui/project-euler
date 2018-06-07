import util
import time

def test_extend_list_of_primes():
    L = util.list_of_primes(1500000)
    P = util.extend_list_of_primes(3000000, L)
    #P = util.list_of_primes(3000000)

def test_list_of_prime_factors():
    t0 = time.time()
    print util.list_of_prime_factors_v2(99999)
    d0 = time.time() - t0
    print d0
    t0 = time.time()
    print util.list_of_prime_factors_v1(99999)
    d1 = time.time() - t0
    print d1
    print "speedup:", d1/d0


def test_list_of_divisors():
    n = 2000000
    st = time.time()
    L1 = util.list_of_divisors_v1(n);
    t1 = time.time() - st
    L1.sort()

    st = time.time()
    L2 = util.list_of_divisors_v2(n);
    t2 = time.time() - st
    L2.sort()

    print "List of Divisors of %d" % (n)
    print "v1 took %.6lf seconds: %s" % (t1, L1)
    print "v2 took %.6lf seconds: %s" % (t2, L2)

def test_prime_factor_generator():
    print list(util.prime_factor_generator(55))
    print list(util.divisorGen(220))


def main():
    test_list_of_divisors()
    test_prime_factor_generator()
    return
    test_list_of_prime_factors()
    test_extend_list_of_primes()

if __name__ == "__main__":
    main()
