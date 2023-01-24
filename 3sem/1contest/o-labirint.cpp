#include <iostream>


struct dp_t
{
    long long prev_value = 0;
    long long cur_value  = 0;
    char symbol          = 0;
};

int main()
{
    int N = 0;
    int M = 0;
    int K = 0;
    std::cin >> N >> M >> K;

    dp_t **dp = new dp_t *[N];
    for (int i = 0; i < N; ++i)
    {
        dp[i] = new dp_t[M];
    }

    int exit_x = 0;
    int exit_y = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            while ((dp[i][j].symbol = getchar()) == '\n');
            if (dp[i][j].symbol == '@')
            {
                dp[i][j].prev_value = 1;
            }
            if (dp[i][j].symbol == '#')
            {
                exit_y = i;
                exit_x = j;
            }
        }
    }

    for (int k = 0; k < K; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (dp[i][j].symbol == '+')
                {
                    continue;
                }

                if (i > 0)
                {
                    dp[i][j].cur_value += dp[i - 1][j].prev_value;
                }
                if (i + 1 < N)
                {
                    dp[i][j].cur_value += dp[i + 1][j].prev_value;
                }
                if (j > 0)
                {
                    dp[i][j].cur_value += dp[i][j - 1].prev_value;
                }
                if (j + 1 < M)
                {
                    dp[i][j].cur_value += dp[i][j + 1].prev_value;
                }
            }
        }
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                dp[i][j].prev_value = dp[i][j].cur_value;
                dp[i][j].cur_value  = 0;
            }
        }
    }

    std::cout << dp[exit_y][exit_x].prev_value << std::endl;

    for (int i = 0; i < N; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;

    return 0;
}