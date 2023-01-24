#include <cassert>
#include <iostream>


long long get_min_attempts_quantity(size_t max_height, size_t balls_reserve)
{
    if (max_height == 1)
    {
        return 0;
    }
    if (balls_reserve == 0)
    {
        return -1;
    }

    long long **dp = new long long *[2];                                                   // dp[i][j] = minimal height that gives us exactly i attempts using j balls
    for (size_t i = 0; i < 2; ++i)
    {
        dp[i] = new long long [balls_reserve + 1];

        dp[i][0] = 1;
    }

    size_t answer = -1;
    for (answer = 1; answer < max_height; ++answer)
    {   
        bool answer_is_found = false;

        for (size_t balls_available = 1; balls_available < balls_reserve + 1; ++balls_available)
        {
            if (answer == 1)
            {
                dp[answer % 2][balls_available] = 2;
            }
            else
            {
                dp[answer % 2][balls_available] = dp[(answer - 1) % 2][balls_available] + dp[(answer - 1) % 2][balls_available - 1];
            }

            if (dp[answer % 2][balls_available] >= max_height)
            {
                answer_is_found = true;

                break;
            }
        }

        if (answer_is_found)
        {
            break;
        }
    }

    for (size_t i = 0; i < 2; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;
    
    return answer;
}

int main()
{
    size_t N = 0;
    size_t K = 0;
    std::cin >> N >> K;

    std::cout << get_min_attempts_quantity(N, K);

    return 0;
}