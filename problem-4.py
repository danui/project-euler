"""
A palindromic number reads the same both ways. The largest palindrome
made from the product of two 2-digit numbers is 9009 = 91 99.

Find the largest palindrome made from the product of two 3-digit
numbers.
"""

import util

i = 999
j = 999
m = 0
while i >= 100:
    j = 999
    while j >= 100:
        if m < i*j:
            s = str(i*j)
            if util.str_is_palindrome(s):
                m = i*j
        j -= 1
    i -= 1
print m
