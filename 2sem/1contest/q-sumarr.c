#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    scanf("%d", &N);

    int cur_elem = 0;
    long long max_sum = LLONG_MIN;
    long long possible_sum = 0;

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &cur_elem);
        possible_sum += cur_elem;
        if (possible_sum > max_sum)
        {
            max_sum = possible_sum;
        }
        
        if (possible_sum < 0)
        {
            possible_sum = 0;
        }
    }

    printf("%lld", max_sum);

    return 0;
}