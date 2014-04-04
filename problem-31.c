#include <stdio.h>

static long long different_ways(long long target, long long *coins)
{
    if (*coins == 0) return 0;
    if (target < 0) return 0;
    if (target == 0) return 1;
    return different_ways(target - *coins, coins)
        +  different_ways(target, coins + 1)
        ;
}

int main(void)
{
    long long ans;
    long long coins[] = {1, 2, 5, 10, 20, 50, 100, 200, 0};
    ans = different_ways(200, coins);
    printf("diffrerent_ways: %lld\n", ans);
    return 0;
}
