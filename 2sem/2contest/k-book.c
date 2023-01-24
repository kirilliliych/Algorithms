#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    long long K = 0;
    long long N = 0;
    scanf("%lld %lld", &K, &N);

    long long sum = 0;
    long long M = 0;
    long long *pages = (long long *) calloc(N, sizeof(long long));
    for (long long i = 0; i < N; ++i)
    {
        scanf("%lld", &pages[i]);
        if (M < pages[i])
        {
            M = pages[i];
        }

        sum += pages[i];
    }

    if (M < sum / K)
    {
        M = sum / K;
    }

    long long toms_now = 0;
    long long cur_pages_sum = 0;
    while (toms_now < K)
    {
        for (long long i = 0; i < N; ++i)
        {
            cur_pages_sum += pages[i];
            
            if (i == N - 1)
            {
                ++toms_now;
                
                if (cur_pages_sum > M)
                {
                    ++toms_now;
                }
            }
            else
            {
                if (cur_pages_sum > M)
                {
                    cur_pages_sum = pages[i];
                    ++toms_now;
                }
            }
        }

        if (toms_now > K)
        {
            toms_now = 0;
            cur_pages_sum = 0;
            ++M;
        }
        else
        {
            break;
        }
    }

    printf("%lld", M);

    free(pages);

    return 0;
}