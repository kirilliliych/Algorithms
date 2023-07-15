#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>


std::vector<int> kasai_arimura_arikawa_lee_park(const std::vector<int> &suf_arr, const std::string &str)
{
    int suf_arr_size = static_cast<int> (suf_arr.size());
    std::vector<int> inversed_suf_arr(suf_arr_size);
    for (int suf_index_alph_order = 0; suf_index_alph_order < suf_arr_size; ++suf_index_alph_order)
    {
        inversed_suf_arr[suf_arr[suf_index_alph_order] - 1] = suf_index_alph_order;
    }
    
    int cur_lcp_size = 0;
    std::vector<int> lcp(suf_arr_size);
    for (int suf_index = 0; suf_index < suf_arr_size; ++suf_index)
    {
        if (inversed_suf_arr[suf_index] == suf_arr_size - 1)
        {
            cur_lcp_size = 0;
        }
        else
        {
            int neighbour = suf_arr[inversed_suf_arr[suf_index] + 1] - 1;
            while ((suf_index + cur_lcp_size < suf_arr_size) &&
                   (neighbour + cur_lcp_size < suf_arr_size) &&
                   (str[suf_index + cur_lcp_size] == str[neighbour + cur_lcp_size]))
            {
                ++cur_lcp_size;
            }
        }

        lcp[inversed_suf_arr[suf_index]] = cur_lcp_size;

        if (cur_lcp_size > 0)
        {
            --cur_lcp_size;
        }
    }

    return lcp;
}


int main()
{
    int N = 0;
    std::cin >> N;
    std::string input = "";
    std::cin >> input;
    std::vector<int> suf_arr(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> suf_arr[i];
    }
    std::vector<int> lcp = kasai_arimura_arikawa_lee_park(suf_arr, input);
    for (int i = 0; i < N - 1; ++i)
    {
        std::cout << lcp[i] << " ";
    }

    return 0;
}
