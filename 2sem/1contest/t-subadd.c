#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    int Q = 0;
    scanf("%d %d", &N, &Q);

    int *numbers = (int *) calloc(N, sizeof(int));
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &numbers[i]);
    }
    long long *magic_array = (long long *) calloc(N, sizeof(long long));
    
    for (int i = 0; i < Q; ++i)
    {
        int left  = 0;
        int right = 0;
        long long value = 0;

        scanf("%d %d %lld", &left, &right, &value);
        magic_array[left] += value;
        magic_array[right + 1] -= value;
    }

    printf("%lld ", numbers[0] + magic_array[0]);
    for (int i = 1; i < N; ++i)
    {
        magic_array[i] += magic_array[i - 1];
        printf("%lld ", numbers[i] + magic_array[i]);
    }

    return 0;
}