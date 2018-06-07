"""
n! means n  (n  1)  ...  3  2  1

For example, 10! = 10  9  ...  3  2  1 = 3628800,

and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0
= 27.

Find the sum of the digits in the number 100!
"""

def solve(n):
    x = 1
    i = 1
    while i <= n:
        x *= i
        while (x % 10) == 0:
            x //= 10
        i += 1
    y = 0
    while x > 0:
        y += x % 10
        x //= 10
    return y

print solve(100)

# alternative??!
print reduce(lambda x, y: x + y, [int(i) for i in str(reduce(lambda x, y: x * y, range(1, 100)))])
