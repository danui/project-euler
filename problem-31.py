# Question
"""
In England the currency is made up of pound and pence and there are
eight coind in general circulation:

    1p, 2p, 5p, 10p, 20p, 50p, 1 pound (100p), and 2 pounds (200p)

It is possible to make 2 pounds in the following way:

    ...

How many different ways can 2 pounds be made using any number of coins?

"""

coins = [1, 2, 5, 10, 20, 50, 100, 200]
#coins = [200, 100, 50, 20, 10, 5, 2, 1]
def different_ways(target, coins, idx):
    if len(coins) == idx:
        return 0
    if (target < 0):
        return 0
    if (target == 0):
        return 1
    return different_ways(target - coins[idx], coins, idx) + different_ways(target, coins, idx+1)

ans = different_ways(200, coins, 0)
print "Different Ways:", ans
