#include <cassert>
#include <cstring>
#include <iostream>


const long long MAX_STR_SIZE = 700;


bool file_name_is_matching_pattern(const char *file_name, const char *pattern, long long file_name_size, long long pattern_size)
{
    assert(file_name != nullptr);
    assert(pattern   != nullptr);

    bool **dp = new bool *[pattern_size + 1];
    for (long long i = 0; i < pattern_size + 1; ++i)
    {
        dp[i] = new bool[file_name_size + 1];
        for (long long j = 0; j < file_name_size + 1; ++j)
        {
            dp[i][j] = false;
        }
    }
    dp[0][0] = true;

    for (long long i = 1; i < pattern_size + 1; ++i)
    {
        if (pattern[i - 1] == '*')
        {
            long long dp_last_line_cur_elem = 0;
            while ((dp_last_line_cur_elem < file_name_size + 1) && (dp[i - 1][dp_last_line_cur_elem] == false))
            {
                dp[i][dp_last_line_cur_elem] = false;

                ++dp_last_line_cur_elem;
            }
            while (dp_last_line_cur_elem < file_name_size + 1)
            {
                dp[i][dp_last_line_cur_elem] = true;

                ++dp_last_line_cur_elem;
            }

            continue;
        }

        for (long long j = 1; j < file_name_size + 1; ++j)
        {
            if ((pattern[i - 1] == file_name[j - 1]) || (pattern[i - 1] == '?'))
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }

    bool result = dp[pattern_size][file_name_size];

    for (long long i = 0; i < pattern_size + 1; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;

    return result;
}


int main()
{
    char file_name[MAX_STR_SIZE + 1] = {};
    char pattern[MAX_STR_SIZE + 1]   = {};
    std::cin >> file_name >> pattern;
    
    long long file_name_size = strlen(file_name);
    long long pattern_size   = strlen(pattern);

    if (file_name_is_matching_pattern(file_name, pattern, file_name_size, pattern_size))
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }


    return 0;
}
