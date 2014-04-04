#include <stdio.h>

#define N 10

unsigned long long value_of(unsigned char A[N])
{
    unsigned long long x;
    unsigned char i;
    x = 0;
    for (i=0; i<N; ++i)
    {
        x *= 10;
        x += A[i];
    }
    return x;
}

int match_rules(unsigned char *A, int n)
{
    if (n == 0) return 1;
    if (A[0] == 0) return 0;
    if (n < 4) return 1;
    if ( (A[1]*100 + A[2]*10 + A[3]) %  2 ) return 0;
    if (n < 5) return 1;
    if ( (A[2]*100 + A[3]*10 + A[4]) %  3 ) return 0;
    if (n < 6) return 1;
    if ( (A[3]*100 + A[4]*10 + A[5]) %  5 ) return 0;
    if (n < 7) return 1;
    if ( (A[4]*100 + A[5]*10 + A[6]) %  7 ) return 0;
    if (n < 8) return 1;
    if ( (A[5]*100 + A[6]*10 + A[7]) % 11 ) return 0;
    if (n < 9) return 1;
    if ( (A[6]*100 + A[7]*10 + A[8]) % 13 ) return 0;
    if (n < 10) return 1;
    if ( (A[7]*100 + A[8]*10 + A[9]) % 17 ) return 0;
    return 1;
}

unsigned long long perm(unsigned char A[N], int k)
{
    unsigned char a, b, i;
    unsigned long long s;
    if (k == N) {
        if (match_rules(A, k))
        {
            if (0)
            {
                printf("NUMBER: ");
                for (i=0; i<N; ++i)
                {
                    printf("%u", A[i]);
                }
                printf("\n");
            }
            return value_of(A);
        }
        return 0;
    } else {
        s = 0;
        for (i=k; i<N; ++i) {
            a = A[i];
            b = A[k];
            A[i] = b;
            A[k] = a;
            if (match_rules(A, k+1)) {
                s += perm(A, k+1);
            }
            A[i] = a;
            A[k] = b;
        }
        return s;
    }
}

int main(void)
{
    unsigned char A[N];
    unsigned char i;
    unsigned long long x;
    for (i=0; i<N; ++i)
    {
        A[i] = i;
    }
    x = perm(A, 0);
    printf("SUM: %llu\n", x);
    return 0;
}
