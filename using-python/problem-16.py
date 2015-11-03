"""
2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
"""

L = str(2**1000)
s = 0
for i in L:
    s += int(i)
print s
