#include <cassert>
#include <climits>
#include <iostream>


long long get_min_mults_quantity(long long **dp, const long long *matrices_dims, const int row, const int col)
{
    assert(dp            != nullptr);
    assert(matrices_dims != nullptr);
    assert(row >= 0);
    assert(col >= 0);

    if (dp[row][col] == LONG_LONG_MAX)
    {
        for (int i = row; i < col; ++i)
        {
            dp[row][col] = std::min(dp[row][col], get_min_mults_quantity(dp, matrices_dims, row, i) + get_min_mults_quantity(dp, matrices_dims, i + 1, col) + 
                                                  matrices_dims[row] * matrices_dims[i + 1] * matrices_dims[col + 1]); 
        }
    }

    return dp[row][col];
}


long long solve(const long long *matrices_dims, const int N)
{
    assert(matrices_dims != nullptr);

    long long **dp = new long long *[N];
    for (int i = 0; i < N; ++i)
    {
        dp[i] = new long long[N];
        for (int j = 0; j < N; j++)
        {
            dp[i][j] = i == j? 0 : LONG_LONG_MAX;
        }
    }

    long long result = get_min_mults_quantity(dp, matrices_dims, 0, N - 1);

    for (int i = 0; i < N; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;

    return result;
}


int main()
{
    int N = 0;
    std::cin >> N;  
    long long *matrices_dims = new long long[N];
    for (int i = 0; i < N; ++i)
    {
        std::cin >> matrices_dims[i];
    }

    std::cout << solve(matrices_dims, N - 1);

    delete [] matrices_dims;

    return 0;
}