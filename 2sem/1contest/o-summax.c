#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    scanf("%d", &N);

    int *A = (int *) calloc(N, sizeof(int));
    int *B = (int *) calloc(N, sizeof(int));

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &B[i]);
    }
    
    int potent_i_pos = 0;
    int i_pos = 0;
    int j_pos = 0;

    for (int j = 0; j < N; ++j)
    {
        if (A[j] > A[potent_i_pos])
            {
                potent_i_pos = j;
            }

        if (B[j] < B[j_pos])
        {

            if (A[potent_i_pos] + B[j] > A[i_pos] + B[j_pos])
            {
                i_pos = potent_i_pos;
                j_pos = j;
            }
        }
        else if (B[j] == B[j_pos])
        {
            if (A[potent_i_pos] > A[i_pos])
            {
                i_pos = potent_i_pos;
                j_pos = j;
            }
        }
        else if (B[j] > B[j_pos])
        {
            j_pos = j;
            i_pos = potent_i_pos;
        }
    }
    
    printf("%d %d", i_pos, j_pos);

    return 0;
}