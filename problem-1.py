"""
if we list all the natural numbers below 10 that are multiples of 3 or
5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
"""


# Let n = number of a value v in 999 is floor(999/v)
#
# Let k = 1+2+3+...+n = n * (n+1) / 2
#
# Thus, sum of all multiples of v is k * v.
def sum_of_multiples(v):
    n = 999 // v
    k = n * (n + 1) // 2
    return k * v

sum_3 = sum_of_multiples(3)
sum_5 = sum_of_multiples(5)
sum_15 = sum_of_multiples(15)

print sum_3 + sum_5 - sum_15
