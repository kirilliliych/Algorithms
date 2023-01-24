#include <cassert>
#include <iostream>
#include <iomanip>

#define aboba std::cout << "aboba " << __LINE__ << std::endl;

int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    long double **dp = new long double *[M + 1];
    for (int i = 0; i < M + 1; ++i)
    {
        dp[i] = new long double[N + 1];
    }
    for (int i = 1; i <= 6 && i <= M; ++i)
    {
        dp[i][1] = 1;
    }

    for (int i = 2; i < M + 1; ++i)
    {
        for (int j = 1; j <= 6 && j < i; ++j)
        {
            for (int k = 1; k <= N - 1; ++k)
            {
                dp[i][k + 1] += dp[i - j][k] / 6;
            }
        }
    }

    long double probability = dp[M][N];

    std::cout << std::fixed << std::setprecision(10) << probability / 6 << std::endl;


    for (int i = 0; i < M + 1; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;

    return 0;
}