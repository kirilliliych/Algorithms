#include <cassert>
#include <cstring>
#include <iostream>


const long long MAX_STRING_SIZE = 30000; 


int main()
{
    char *input1 = new char[MAX_STRING_SIZE + 1];
    char *input2 = new char[MAX_STRING_SIZE + 1];
    std::cin >> input1 >> input2;
    long long size_1 = strlen(input1);
    long long size_2 = strlen(input2);

    long long *dp = new long long[MAX_STRING_SIZE + 2];

    char *answer_ptr_input_1 = input1;
    long long cur_max_length = 0;
    for (long long matrix_row_index = 1; matrix_row_index <= size_2; ++matrix_row_index)
    {
        dp[0] = 0;

        for (long long matrix_col_index = size_1; matrix_col_index >= 1; --matrix_col_index)
        {
            dp[matrix_col_index] = input1[matrix_col_index - 1] == input2[matrix_row_index - 1] ?  
                                   1 + dp[matrix_col_index - 1] : 0;

            if (dp[matrix_col_index] == cur_max_length)
            {
                char *potential_answer_input_1 = input1 + matrix_col_index - cur_max_length;
                if (strncmp(potential_answer_input_1, answer_ptr_input_1, cur_max_length) < 0)
                {
                    answer_ptr_input_1 = potential_answer_input_1;
                }
            }
            else if (dp[matrix_col_index] > cur_max_length)
            {
                cur_max_length = dp[matrix_col_index];

                answer_ptr_input_1 = input1 + matrix_col_index - cur_max_length;
            }
        }
    }
    
    for (long long i = 0; i < cur_max_length; ++i)
    {
        std::cout << *(answer_ptr_input_1 + i);
    }
    
    delete [] dp;

    delete [] input2;
    delete [] input1;

    return 0;
}