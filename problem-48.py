"""

Problem 48

The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... +
1000^1000.

"""

N = 1000
base = 10000000000
sum = 0
for i in xrange(1, N+1):
    num = 1
    for j in xrange(i):
        num = (num * i) % base
    sum = (sum + num) % base
print sum
