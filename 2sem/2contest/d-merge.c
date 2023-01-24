#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long Merge(long long *array, long long *index, long long *real_index, long long new_value, long long N)
{
    assert(array      != NULL);
    assert(index      != NULL);
    assert(real_index != NULL);

    long long sum = 0;
    int added = 0;
    for (long long iter = *real_index; iter < N; ++(*index), ++(*real_index), ++iter)
    {
        added = 0;
        if (*index % 2 == 0)
        {
            sum += array[*real_index];
            ++added;
        }

        if (new_value >= array[*real_index])
        {
            continue;
        }

        break;
    }

    if (*index % 2 == 0)
    {
        if (added == 1)
        {
            sum -= array[*real_index];
        }
        sum += new_value;
    }

    ++(*index);

    return sum;
}

int main()
{
    long long N = 0;
    scanf("%lld\n", &N);

    long long *array = (long long *) calloc(N, sizeof(long long));
    for (long long i = 0; i < N; ++i)
    {
        scanf("%lld", &array[i]);
    }

    long long sum = 0;
    long long index = 0;
    long long real_index = 0;
    long long new_value = 0;
    long long scanfed = 0;

    while (real_index < N)
    {   
        if (scanfed >= N)
        {
            break;
        }
        scanf("%lld", &new_value);
        ++scanfed;

        long long add_sum = Merge(array, &index, &real_index, new_value, N);
        sum += add_sum;
    }

    while (real_index < N)
    {
        if (index % 2 == 0)
        {
            sum += array[real_index];
        }

        ++real_index;
        ++index;
    }

    while (scanfed < N)
    {
        scanf("%lld", &new_value);
        ++scanfed;

        if (index % 2 == 0)
        {
            sum += new_value;
        }

        ++index;
    }

    printf("%lld", sum % 1000000000);

    free(array);

    return 0;
}