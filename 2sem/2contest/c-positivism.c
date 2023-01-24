#include <stdio.h>
#include <stdlib.h>

struct row_col
{
    int number;
    char row_or_col;
};

int main()
{
    int N = 0;
    int M = 0;
    scanf("%d %d", &N, &M);
    int *matrix = (int *) calloc(N * M, sizeof(int));

    for (int j = 0; j < M; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            scanf("%d", &matrix[j * N + i]);
        }
    }

    struct row_col *buffer = (struct row_col *) calloc(100 * N * M, sizeof(struct row_col));
    int place = 0;

    int impossible = 0;
    for (int iterator = 0; iterator < 100; ++iterator)
    {
        int good = 0;

        for (int y = 0; y < N; ++y)
        {
            long long sum_row = 0;
            for (int x = 0; x < M; ++x)
            {
                sum_row += *(matrix + y * M + x);
            }
            
            if (sum_row < 0)
            {
                good = 1;
                for (int x = 0; x < M; ++x)
                {
                    *(matrix + y * M + x) *= -1;
                }

                buffer[place].number = y;
                buffer[place].row_or_col = 'l';
                ++place;
            }
        }

        for (int x = 0; x < M; ++x)
        {
            long long sum_col = 0;
            for (int y = 0; y < N; ++y)
            {
                sum_col += *(matrix + y * M + x);
            }
            if (sum_col < 0)
            {
                good = 1;
                for (int y = 0; y < N; ++y)
                {
                    *(matrix + y * M + x) *= -1;
                }

                buffer[place].number = x;
                buffer[place].row_or_col = 'c';
                ++place;
            }
        }

        if (good == 0)
        {
            break;
        }

        if (iterator == 99)
        {
            impossible = 1;
        }
    }

    if (impossible == 1)
    {
        printf("Impossible");
    }
    else
    {
        for (int i = 0; i < place; ++i)
        {
            printf("%c %d\n", buffer[i].row_or_col, buffer[i].number);
        }
    }

    free(buffer);
    free(matrix);

    return 0;
}