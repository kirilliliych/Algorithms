#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int THRESHOLD = 2;

void BubbleSort(long long *array, long long low, long long high, long long *inv_quantity)
{
    assert(array != NULL);

    for (long long i = low; i <= high; ++i)
    {
        for (long long j = low; j < high; ++j)
        {
            if (array[j] > array[j + 1])
            {
                long long temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                ++(*inv_quantity);  
            }
        }
    }
}

void Merge(long long *array, long long low, long long middle, long long high, long long *inv_quantity)
{
    assert(array        != NULL);
    assert(inv_quantity != NULL);
    
    long long *result = (long long *) calloc(high - low + 1, sizeof(long long));

    long long *ptr1 = array + low;
    long long *ptr2 = array + middle + 1;

    long long place = 0;

    while ((ptr1 <= array + middle) && (ptr2 <= array + high))
    {
        if (*ptr1 <= *ptr2)
        {
            result[place] = *ptr1;
            ++ptr1;
        }
        else
        {
            result[place] = *ptr2;
            ++ptr2;

            *inv_quantity += (long long) (ptr2 - array - low - place - 1);
        }

        ++place;
    }

    while (ptr1 <= array + middle)
    {
        result[place] = *ptr1;

        ++ptr1;
        ++place;
    }

    while (ptr2 <= array + high)
    {
        result[place] = *ptr2;

        ++ptr2;
        ++place;
    }
    
    memmove(array + low, result, (high - low + 1) * sizeof(long long));

    free(result);
}

void MergeSort(long long *array, long long low, long long high, long long *inv_quantity)
{
    assert(array        != NULL);
    assert(inv_quantity != NULL);

    if (high - low < THRESHOLD)
    {
        BubbleSort(array, low, high, inv_quantity);
    }
    else
    {
        long long middle = (low + high) >> 1;
        MergeSort(array, low, middle, inv_quantity);
        MergeSort(array, middle + 1, high, inv_quantity);
        Merge(array, low, middle, high, inv_quantity);
    }

}

int main()
{
    long long N = 0;
    scanf("%lld", &N);

    long long *array = (long long *) calloc(N, sizeof(long long));
    for (int i = 0; i < N; ++i) 
    {
        scanf("%lld", &array[i]);
    }

    long long inv_quantity = 0;
    MergeSort(array, 0, N - 1, &inv_quantity);

    printf("%lld", inv_quantity);

    free(array);

    return 0;
}