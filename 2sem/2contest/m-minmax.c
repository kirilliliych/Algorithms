#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long Max(long long first, long long second)
{
    return first > second ? first : second;
}

void BinarySearch(long long *A_arr, long long *B_arr, long long *index,
                  long long left,   long long right)
{
    assert(A_arr != NULL);
    assert(B_arr != NULL);
    assert(index != NULL);

    if (left > right)
    {
        return;
    }

    long long middle = (left + right) / 2;

    long long cur_min_max = Max(A_arr[middle], B_arr[middle]);
    if (Max(A_arr[*index], B_arr[*index]) > cur_min_max)
    {
        *index = middle;
    }

    if (cur_min_max == A_arr[middle])
    {
        BinarySearch(A_arr, B_arr, index, left, middle - 1);
    }
    else
    {
        BinarySearch(A_arr, B_arr, index, middle + 1, right);
    }
}

int main()
{
    long long N = 0;
    long long M = 0;
    long long L = 0;
    scanf("%lld %lld %lld", &N, &M, &L);

    long long **arrays = (long long **) calloc(N + M, sizeof(long long *));
    for (long long i = 0; i < N + M; ++i)
    {
        arrays[i] = (long long *) calloc(L, sizeof(long long));
        for (long long j = 0; j < L; ++j)
        {
            scanf("%lld", &((arrays[i])[j]));
        }
    }

    long long Q = 0;
    scanf("%lld", &Q);

    long long A_index = 0;
    long long B_index = 0;
    for (long long i = 0; i < Q; ++i)
    {
        scanf("%lld %lld", &A_index, &B_index);
        --A_index;
        B_index += N - 1;

        long long index = 0;
        BinarySearch(arrays[A_index], arrays[B_index], &index, 0, L - 1);
        printf("%lld\n", index + 1);
    }

    for (long long i = 0; i < N + M; ++i)
    {
        free(arrays[i]);
    }
    free(arrays);

    return 0;
}