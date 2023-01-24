#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    int M = 0;

    scanf("%d", &N);
    scanf("%d", &M);

    int *A = (int *) calloc(N, sizeof(int));
    int *B = (int *) calloc(M, sizeof(int));

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &A[i]);
    }

    for(int i = 0; i < M; ++i)
    {
        scanf("%d", &B[i]);
    }

    int *a_ptr = A;
    int *b_ptr = B;

    while ((a_ptr - A < N) && (b_ptr - B < M))
    {
        if (*a_ptr < *b_ptr)
        {
            ++a_ptr;
        }
        else if (*a_ptr > *b_ptr)
        {
            ++b_ptr;
        }
        else
        {
            printf("%d ", *a_ptr);

            ++a_ptr;
            ++b_ptr;
        }
    }

    return 0;
}