#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>


struct RefrainContext
{
    size_t enterings_quantity_ = 0;
    size_t size_               = 0;
    size_t index_              = 0;
};


struct SuffixContext
{
    int initial_index = 0;
    int rank          = 0;
    int next_rank     = 0;
};

bool comparator(const SuffixContext &suf1, const SuffixContext &suf2)
{
    return suf1.rank < suf2.rank ? true : suf1.rank == suf2.rank ? suf1.next_rank < suf2.next_rank ? true : false : false;
}

std::vector<int> build_suff_arr(const std::string &str)
{
    int str_size = static_cast<int> (str.size());
    std::vector<SuffixContext> suffixes(str_size);
 
    for (int suffix_index = 0; suffix_index < str_size; ++suffix_index)
    {
        suffixes[suffix_index].initial_index = suffix_index;
        suffixes[suffix_index].rank      = str[suffix_index];
        suffixes[suffix_index].next_rank = suffix_index == str_size - 1 ? -1 : str[(suffix_index + 1)];
    }

    std::sort(suffixes.begin(), suffixes.end(), comparator);

    for (int sorted_length = 2; sorted_length < str_size; sorted_length *= 2)
    {
        int prev_rank = suffixes[0].rank;
        suffixes[0].rank = 0;
 
        std::vector<int> intermediary_order(str_size);
        intermediary_order[suffixes[0].initial_index] = 0;
        int cur_rank = 0;
        for (int suffix_index = 1; suffix_index < str_size; ++suffix_index)
        {   
            bool equal_to_prev = false;

            if ((suffixes[suffix_index].rank == prev_rank) &&
                (suffixes[suffix_index].next_rank == suffixes[suffix_index - 1].next_rank))
            {
                equal_to_prev = true;
            }

            prev_rank = suffixes[suffix_index].rank;
            if (!equal_to_prev)
            {
                ++cur_rank;
            }
            suffixes[suffix_index].rank = cur_rank;

            intermediary_order[suffixes[suffix_index].initial_index] = suffix_index;
        }

        for (int suffix_index = 0; suffix_index < str_size; ++suffix_index)
        {
            int next_suffix_real_index = suffixes[suffix_index].initial_index + sorted_length;
            suffixes[suffix_index].next_rank = next_suffix_real_index >= str_size ? -1 : suffixes[intermediary_order[next_suffix_real_index]].rank;
        }
 
        std::sort(suffixes.begin(), suffixes.end(), comparator);
    }
 
    std::vector<int> result(str_size);
    for (int i = 0; i < str_size; ++i)
    {
        result[i] = suffixes[i].initial_index + 1;
    }

    return result;
}

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

RefrainContext find_biggest_refrain(const std::string &str)
{
    std::vector<int> suff_arr = build_suff_arr(str);
    std::vector<int> lcp      = kasai_arimura_arikawa_lee_park(suff_arr, str);

    size_t str_size = str.size();
    std::stack<RefrainContext> stack;

    RefrainContext max_refrain{1, str_size, 0};

    for (size_t pos = 0; pos < str_size; ++pos)
    {
        size_t cur_refrain_enterings_quantity = 1;

        while (!stack.empty() && (lcp[pos] <= stack.top().size_))
        {
            RefrainContext largest_prev = stack.top();
            stack.pop();

            cur_refrain_enterings_quantity += largest_prev.enterings_quantity_;
            if (cur_refrain_enterings_quantity  * largest_prev.size_ >=
                max_refrain.enterings_quantity_ * max_refrain.size_)
            {
                max_refrain = {cur_refrain_enterings_quantity, 
                               largest_prev.size_,
                               static_cast<size_t> (suff_arr[largest_prev.index_]) - 1};
            }
        }

        if (stack.empty() || (lcp[pos] > stack.top().size_))
        {
            stack.push({cur_refrain_enterings_quantity, static_cast<size_t> (lcp[pos]), pos});
        }
    }

    return max_refrain;
}

 
int main()
{
    size_t n = 0;
    size_t m = 0;
    std::cin >> n >> m;
    
    std::string input;
    for (size_t i = 0; i < n; ++i)
    {
        size_t value = 0;
        std::cin >> value;
        input.push_back(static_cast<char> (value + '0'));
    }

    RefrainContext max_refrain = find_biggest_refrain(input);
    std::cout << max_refrain.enterings_quantity_ * max_refrain.size_ << "\n"
              << max_refrain.size_ << std::endl;
    for (size_t i = max_refrain.index_; i < max_refrain.index_ + max_refrain.size_; ++i)
    {
        std::cout << input[i] << " ";
    }


    return 0;
}
