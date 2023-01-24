#include <cassert>
#include <cstring>
#include <cmath>
#include <iostream>

const size_t MAX_STRING_SIZE = 1000;

void dump(int **board, size_t input1_size, size_t input2_size)
{
    assert(board != nullptr);

    for (int i = 0; i < input1_size; ++i)
    {
        for (int j = 0; j < input2_size; ++j)
        {
            std::cout << board[i][j] << " ";
        }

        std::cout << std::endl; 
    }
}

int main()
{
    char input1[MAX_STRING_SIZE] = {};
    char input2[MAX_STRING_SIZE] = {};

    std::cin >> input1;
    std::cin >> input2;
    size_t input1_size = strlen(input1);
    size_t input2_size = strlen(input2);

    int **dp = new int *[input1_size + 1];
    for (int i = 0; i < input1_size + 1; ++i)
    {
        dp[i] = new int[input2_size + 1];
    }
    for (int i = 0; i < input1_size + 1; ++i)
    {
        dp[i][0] = i;
    }
    for (int i = 0; i < input2_size + 1; ++i)
    {
        dp[0][i] = i;
    }
    
    for (int i = 1; i < input1_size + 1; ++i)
    {
        for (int j = 1; j < input2_size + 1; ++j)
        {
            dp[i][j] = std::min(dp[i][j - 1], dp[i - 1][j - 1]);
            dp[i][j] = std::min(dp[i - 1][j], dp[i][j]);
            
            if ((dp[i][j] == dp[i - 1][j - 1]) && (input1[i - 1] == input2[j - 1]))
            {
                --dp[i][j];
            }

            ++dp[i][j];
        }
    }

    std::cout << dp[input1_size][input2_size];

    for (int i = 0; i < input1_size + 1; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;

    return 0;
}