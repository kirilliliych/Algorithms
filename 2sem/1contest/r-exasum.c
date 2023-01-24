#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int compare(const void *elem_1, const void *elem_2)
{
    assert(elem_1 != NULL);
    assert(elem_2 != NULL);

    return *((int *) elem_1) - *((int *) elem_2);
}

int main()
{
    int N = 0;
    int M = 0;
    scanf("%d %d", &N, &M);

    int *array = (int *) calloc(N, sizeof(int));

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &array[i]);
    }

    qsort(array, N, sizeof(int), compare);

    for (int i = 0; i < M; ++i)
    {
        int sample = 0;
        scanf("%d", &sample);

        int *begin_ptr = array;
        int *end_ptr   = array + N - 1;

        while (begin_ptr < end_ptr)
        {
            if (*begin_ptr + *end_ptr > sample)
            {
                --end_ptr;
            }
            else if (*begin_ptr + *end_ptr < sample)
            {
                ++begin_ptr;
            }
            else 
            {
                printf("%d %d\n", *begin_ptr, *end_ptr);

                break;
            }

            if (begin_ptr >= end_ptr)
            {
                printf("Not found\n");
            }
        }
    }

    free(array);

    return 0;
}