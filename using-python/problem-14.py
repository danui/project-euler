"""
The following iterative sequence is defined for the set of positive
integers:

n = n/2 (n is even)
n = 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following
sequence:

13  40  20  10  5  16  8  4  2  1

It can be seen that this sequence (starting at 13 and finishing at 1)
contains 10 terms. Although it has not been proved yet (Collatz
Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one
million.
"""

def gen_length_of_chain():
    known = {1:1}
    def f(n):
        if n in known:
            return known[n]
        L = [n]
        s = 1
        while True:
            i = L[-1]
            if (i == 1):
                s = 1
                break
            elif (i in known):
                s = known[i]
                break
            elif (i % 2) == 0:
                L.append(i//2)
            else:
                L.append(i * 3 + 1)
        for i in L[::-1]:
            known[i] = s
            s += 1
        return known[n]
    return f
length_of_chain = gen_length_of_chain()

def main():
    x = length_of_chain(1)
    j = 1
    for i in xrange(1,1000000):
        y = length_of_chain(i)
        if x < y:
            x = y
            j = i
    print "Longest chain produced by %d has length %d" %(j,x)

main()

