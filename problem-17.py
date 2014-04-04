"""
If the numbers 1 to 5 are written out in words: one, two, three, four,
five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were
written out in words, how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred
and forty-two) contains 23 letters and 115 (one hundred and fifteen)
contains 20 letters. The use of "and" when writing out numbers is in
compliance with British usage.
"""


A_11_19 = """eleven
twelve
thirteen
fourteen
fifteen
sixteen
seventeen
eighteen
nineteen""".split("\n")

A_1_9 = """one
two
three
four
five
six
seven
eight
nine""".split("\n")

A_20_plus = """twenty
thirty
forty
fifty
sixty
seventy
eighty
ninety""".split("\n")

def stringify(_k):
    k = _k
    n_thousands = k // 1000
    k = k % 1000
    n_hundreds = k // 100
    k = k % 100
    n_tens = k // 10
    k = k % 10
    n_ones = k
    S = ""
    if n_thousands > 0:
        S += A_1_9[n_thousands-1] + " thousand"
    if n_hundreds > 0:
        S += A_1_9[n_hundreds-1] + " hundred"
    if S != "" and (n_tens > 0 or n_ones > 0):
        S += " and "
    if n_tens >= 2:
        S += A_20_plus[n_tens-2]
        if n_ones > 0:
            S += " " + A_1_9[n_ones-1]
    elif n_tens >= 1:
        if n_ones == 0:
            S += "ten"
        else:
            S += A_11_19[n_ones-1]
    else:
        if n_ones > 0:
            S += A_1_9[n_ones-1]
    return S


def slen(A):
    s = 0
    for i in A:
        s += len(i)
    return s

N = 0
for i in xrange(1,1001):
    L = stringify(i).split(" ")
    N += slen(L)
print N

