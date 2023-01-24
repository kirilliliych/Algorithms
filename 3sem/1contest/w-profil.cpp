#include <cassert>
#include <iostream>


bool check_compatibility(size_t mask1, size_t mask2, int mask_capacity_deg)
{
    assert(mask_capacity_deg > 0);

    for (size_t i = (1ull << (mask_capacity_deg - 1)); i > 1; i >>= 1)
    {
        if ((((mask1 & i) != 0) && ((mask2 & i) != 0) && ((mask1 & (i >> 1)) != 0) && ((mask2 & (i >> 1)) != 0)) ||
            (((mask1 & i) == 0) && ((mask2 & i) == 0) && ((mask1 & (i >> 1)) == 0) && ((mask2 & (i >> 1)) == 0)))
        {
            return false;
        }
    }

    return true;
}



long long days_for_master_to_live(int N, int M)
{
    assert(N > 0);
    assert(M > 0);

    size_t profile_compatibility_dim = 1llu << N;
    bool **profile_compatibility = new bool *[profile_compatibility_dim];
    for (size_t i = 0; i < profile_compatibility_dim; ++i)
    {
        profile_compatibility[i] = new bool[profile_compatibility_dim];
    }
    for (size_t mask1 = 0; mask1 < profile_compatibility_dim; ++mask1)
    {
        for (size_t mask2 = 0; mask2 < profile_compatibility_dim; ++mask2)
        {
            profile_compatibility[mask1][mask2] = check_compatibility(mask1, mask2, N);
        }
    }

    long long **dp = new long long *[M];
    for (int i = 0; i < M; ++i)
    {
        dp[i] = new long long [profile_compatibility_dim];
    }
    
    for (size_t i = 0; i < profile_compatibility_dim; ++i)
    {
        dp[0][i] = 1;
    }

    for (int cols = 1; cols < M; ++cols)
    {
        for (size_t i = 0; i < profile_compatibility_dim; ++i)
        {
            for (size_t j = 0; j < profile_compatibility_dim; ++j)
            {
                dp[cols][i] += dp[cols - 1][j] * (profile_compatibility[j][i] ? 1 : 0);
            }
        }
    }

    long long days_quantity = 0;
    for (size_t i = 0; i < profile_compatibility_dim; ++i)
    {
        days_quantity += dp[M - 1][i];
    }

    for (size_t i = 0; i < M; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;
    for (size_t i = 0; i < profile_compatibility_dim; ++i)
    {
        delete [] profile_compatibility[i];
    }
    delete [] profile_compatibility;

    return days_quantity;
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;
    if (N > M)
    {
        std::swap(N, M);
    }
    std::cout << days_for_master_to_live(N, M);

    return 0;
}