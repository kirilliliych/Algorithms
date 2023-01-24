#include <cassert>
#include <iostream>


long long max(long long v1, long long v2)
{
    return v1 > v2 ? v1 : v2;
}

int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    long long **dp = new long long *[N];
    for (int i = 0; i < N; ++i)
    {
        dp[i] = new long long[M];
        for (int j = 0; j < M; ++j)
        {
            std::cin >> dp[i][j];
        }
    }

    for (int j = 0; j < M; ++j)
    {
        for (int i = 1; i < N; ++i)
        {
            dp[i][j] += dp[i - 1][j];
        }
    }

    long long result = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = i; j < N; ++j)
        {           
         long long cur_line_sum = 0;
            for (int k = 0; k < M; ++k)
            {
                cur_line_sum = i > 0 ? max(0, cur_line_sum + dp[j][k] - dp[i - 1][k]) : max(0, cur_line_sum + dp[j][k]);
                result = max(result,  cur_line_sum);
            }
        }
    }

    std::cout << result;


    for (int i = 0; i < N; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;

    return 0;
}