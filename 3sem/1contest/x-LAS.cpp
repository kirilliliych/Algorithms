#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>


int max(int arg1, int arg2)
{
    return arg1 > arg2 ? arg1 : arg2;
}


int *get_LAS(int *elems, int N, int *LAS_length)
{
    assert(elems      != nullptr);
    assert(LAS_length != nullptr);

    int *dp = new int[N + 1];
    dp[0] = INT_MIN;
    for (int i = 1; i <= N; ++i)
    {
        dp[i] = INT_MAX;
    }

    int *last_elem_pos = new int[N + 1];
    last_elem_pos[0]   = INT_MIN;
    int *prev_for_elem = new int[N];
    
    for (int i = 0; i < N; ++i)
    {
        int upper_bound_index = std::upper_bound(dp, dp + N, elems[i]) - dp;

        if ((dp[upper_bound_index - 1] < elems[i]) && (elems[i] < dp[upper_bound_index]))
        {
            dp[upper_bound_index]            = elems[i];
            last_elem_pos[upper_bound_index] = i;
            prev_for_elem[i]                 = last_elem_pos[upper_bound_index - 1];

            *LAS_length = max(*LAS_length, upper_bound_index);
        }   
    }

    int *indexes = new int[N];
    int pos_to_write_new_index = 0;
    int cur_last_elem_pos = last_elem_pos[*LAS_length];
    while (cur_last_elem_pos != INT_MIN)
    {
        indexes[pos_to_write_new_index] = cur_last_elem_pos;
        cur_last_elem_pos = prev_for_elem[cur_last_elem_pos];

        ++pos_to_write_new_index;
    }


    delete [] prev_for_elem;
    delete [] last_elem_pos;
    delete [] dp;

    return indexes;
}


int main()
{
    int N = 0;
    std::cin >> N;
    
    int *elems = new int[N];
    for (int i = 0; i < N; ++i)
    {
        std::cin >> elems[i];
    }

    int LAS_length   = 0;
    int *LAS_indexes = get_LAS(elems, N, &LAS_length); 

    std::cout << LAS_length << std::endl;
    for (int i = LAS_length - 1; i >= 0; --i)
    {
        std::cout << LAS_indexes[i] << " ";
    }

    delete [] LAS_indexes;
    delete [] elems;

    return 0;
}