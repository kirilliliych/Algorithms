#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct subsum_parameters
{
    long long sum;
    int coins_used;
};

int Comparator(const void *sum1, const void *sum2)
{
    assert(sum1 != NULL);
    assert(sum2 != NULL);

    if (((struct subsum_parameters *) sum1)->sum != ((struct subsum_parameters *) sum2)->sum)
    {
        return ((struct subsum_parameters *) sum1)->sum - ((struct subsum_parameters *) sum2)->sum;
    }
    else
    {
        return ((struct subsum_parameters *) sum2)->coins_used - ((struct subsum_parameters *) sum1)->coins_used;
    }
}

void GetSubsums(struct subsum_parameters *subsums_array, int *coins_values, int coins_number)
{
    assert(subsums_array != NULL); 
    assert(coins_values  != NULL);

    for (long long i = 0; i < (1 << coins_number); ++i)
    {
        long long mask = i;
        int coin_index = coins_number - 1;

        while (mask > 0)
        {
            if (mask & 1)
            {
                subsums_array[i].sum += coins_values[coin_index];
                ++subsums_array[i].coins_used;
            }
            mask >>= 1;
            --coin_index;
        }
    }
}

int GetMinCoinsNumber(struct subsum_parameters *subsums_array, int *coins_values, int coins_number, long long price)
{
    assert(subsums_array != NULL); 
    assert(coins_values  != NULL);

    qsort(subsums_array, 1 << coins_number, sizeof(struct subsum_parameters), Comparator);

    if (subsums_array[(1 << coins_number) - 1].sum * 2 < price)
    {
        printf("Impossible");

        return -2; 
    }

    int min_coins_number = coins_number * 2 + 1;

    for (long long i = (1 << coins_number) - 1; i > - 1; --i)
    {
        if (subsums_array[i].sum == price)
        {
            if (subsums_array[i].coins_used < min_coins_number)
            {
                min_coins_number = subsums_array[i].coins_used;
            }
        }

        for (int j =  (1 << coins_number) - 1; j > -1; --j)
        {
            if (subsums_array[i].sum + subsums_array[j].sum == price)
            {
                if (subsums_array[i].coins_used + subsums_array[j].coins_used < min_coins_number)
                {
                    min_coins_number = subsums_array[i].coins_used + subsums_array[j].coins_used;
                }
            }    
        }
    }

    if (min_coins_number == coins_number * 2 + 1)
    {
        printf("Change");

        return -1;
    }

    return min_coins_number;
}

int main()
{
    long long V = 0;
    int N = 0;
    scanf("%lld %d", &V, &N);

    int *coins = (int *) calloc(N, sizeof(int));
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &coins[i]);
    }

    struct subsum_parameters *subsums_array = (struct subsum_parameters *) calloc(1 << N, sizeof(struct subsum_parameters));
    GetSubsums(subsums_array, coins, N);
    
    int min_coins_number = GetMinCoinsNumber(subsums_array, coins, N, V);
    if (min_coins_number > 0)
    {
        printf("%d", min_coins_number);
    }

    free(coins);
    free(subsums_array);
    return 0;
}