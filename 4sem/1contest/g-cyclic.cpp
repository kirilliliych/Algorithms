#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>


const size_t RADIX = 29;
const size_t MOD1  = 1e9 + 7;
const size_t MOD2  = 1e9 + 9;


struct HashedPair
{
    size_t operator ()(const std::pair<size_t, size_t> &pair) const
    {
        return pair.first * RADIX + pair.second;
    }
};


size_t lower_case_row_position(char symb)
{
    return symb - 'a' + 1;
}

size_t moduled_pow(size_t radix, size_t mod, size_t pow)
{
    size_t ans = 1;
    while (pow > 0)
    {
        ans *= radix;
        ans %= mod;

        --pow;
    }

    return ans;
}

std::vector<size_t> build_hashed_moduled_prefix_arr(const std::string &str, size_t radix, size_t mod)
{
    size_t str_size = str.size();
    std::vector<size_t> prefix_arr_hash(str_size, 1);
    prefix_arr_hash[0] = lower_case_row_position(str[0]);
    for (size_t i = 1; i < str_size; ++i)
    {
        prefix_arr_hash[i] = (prefix_arr_hash[i - 1] * radix + lower_case_row_position(str[i])) % mod;
    }

    return prefix_arr_hash;
}


int main()
{
    std::string pattern = "";
    std::string text    = "";
    std::cin >> pattern >> text;

    pattern += pattern;
    size_t pattern_size      = pattern.size();
    size_t pattern_true_size = pattern_size / 2;
    size_t text_size         = text.size();
    if (text_size < pattern_true_size)
    {
        std::cout << "0";

        return 0;
    }

    size_t pattern_true_size_pow1           = moduled_pow(RADIX, MOD1, pattern_true_size);
    size_t pattern_true_size_pow2           = moduled_pow(RADIX, MOD2, pattern_true_size);
    std::vector<size_t> pattern_prefix_arr1 = build_hashed_moduled_prefix_arr(pattern, RADIX, MOD1);
    std::vector<size_t> pattern_prefix_arr2 = build_hashed_moduled_prefix_arr(pattern, RADIX, MOD2);
    std::vector<size_t> text_prefix_arr1    = build_hashed_moduled_prefix_arr(text, RADIX, MOD1);
    std::vector<size_t> text_prefix_arr2    = build_hashed_moduled_prefix_arr(text, RADIX, MOD2);
    
    std::unordered_set<std::pair<size_t, size_t>, HashedPair> pattern_cyclic_shifts{};
    for (size_t i = pattern_true_size - 1; i < pattern_size; ++i)
    {
        size_t hash1_excess_part = i == pattern_true_size - 1 ? 0 : pattern_prefix_arr1[i - pattern_true_size];
        size_t hash2_excess_part = i == pattern_true_size - 1 ? 0 : pattern_prefix_arr2[i - pattern_true_size];
        size_t pattern_cyclic_shift_hash1 = (pattern_prefix_arr1[i] - hash1_excess_part * pattern_true_size_pow1 % MOD1) % MOD1;
        size_t pattern_cyclic_shift_hash2 = (pattern_prefix_arr2[i] - hash2_excess_part * pattern_true_size_pow2 % MOD2) % MOD2;
        pattern_cyclic_shifts.insert({pattern_cyclic_shift_hash1, pattern_cyclic_shift_hash2});
    }

    size_t enterings = 0;
    for (size_t i = pattern_true_size - 1; i < text_size; ++i)
    {
        size_t hash1_excess_part = i == pattern_true_size - 1 ? 0 : text_prefix_arr1[i - pattern_true_size];
        size_t hash2_excess_part = i == pattern_true_size - 1 ? 0 : text_prefix_arr2[i - pattern_true_size];
        size_t text_substring_hash1 = (text_prefix_arr1[i] - hash1_excess_part * pattern_true_size_pow1 % MOD1) % MOD1;
        size_t text_substring_hash2 = (text_prefix_arr2[i] - hash2_excess_part * pattern_true_size_pow2 % MOD2) % MOD2;
        enterings += pattern_cyclic_shifts.count({text_substring_hash1, text_substring_hash2});
    }

    std::cout << enterings;

    return 0;
}
