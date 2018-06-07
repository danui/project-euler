"""
You are given the following information, but you may prefer to do some
research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.

A leap year occurs on any year evenly divisible by 4, but not on a
century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth
century (1 Jan 1901 to 31 Dec 2000)?
"""

def is_leap_year(y):
    if (y % 400) == 0:
        return True
    if (y % 100) == 0:
        return False
    if (y % 4) == 0:
        return True
    return False

def days_in_month(y, m):
    if m == 2:
        if is_leap_year(y):
            return 29
        return 28
    if m in [4,6,9,11]:
        return 30
    return 31

dow=2
y = 1901
m = 1
count = 0
while y < 2001:
    while m <= 12:
        if dow == 0:
            print y, m, dow
            count += 1
        dim = days_in_month(y, m)
        dow = (dow + dim) % 7
        m += 1
    m -= 12
    y += 1
print count
