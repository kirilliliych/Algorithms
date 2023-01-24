#include <cassert>
#include <cstring>
#include <iostream>


const int MAX_STRING_SIZE = 30;


int main()
{
    char *input = new char[MAX_STRING_SIZE + 1];
    std::cin >> input;
    size_t input_size = strlen(input);
    int **dp = new int *[input_size];
    for (int i = 0; i < input_size; ++i)
    {
        dp[i] = new int[input_size];
        dp[i][i] = 1;
    }

    for (int str_len = 1; str_len < input_size + 1; ++str_len)
    {
        for (int begin = 0; begin + str_len < input_size; ++begin)
        {
            int end = begin + str_len;
            if (input[begin] == input[end])
            {
                dp[begin][end] = dp[begin][end - 1] + dp[begin + 1][end] + 1;
            }
            else
            {
                dp[begin][end] = dp[begin][end - 1] + dp[begin + 1][end] - dp[begin + 1][end - 1];
            }
        }
    }

    std::cout << dp[0][input_size - 1];

    for (int i = 0; i < input_size; ++i)
    {
        delete [] dp[i];
    }
    delete [] input;

    return 0;
}