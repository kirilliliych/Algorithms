#include <cassert>
#include <iostream>
#include <vector>


uint64_t get_gcd(uint64_t val1, uint64_t val2)
{
    while (val2 > 0)
    {
        val1 %= val2;
        std::swap(val1, val2);
    }

    return val1;
}


uint64_t get_coprime_gcds_level(std::vector<std::vector<uint64_t>> &gcds, uint64_t size)
{
    for (uint64_t gcd_level = 1; gcd_level < size; ++gcd_level)
    {
        for (uint64_t gcd_row_index = 0; gcd_row_index < size - gcd_level; ++gcd_row_index)
        {
            uint64_t cur_gcd = get_gcd(gcds[gcd_level - 1][gcd_row_index],
                                       gcds[gcd_level - 1][gcd_row_index + 1]);
            if (cur_gcd == 1)
            {
                return gcd_level;
            }
            gcds[gcd_level].push_back(cur_gcd);
        }
    }

    return 0;
}


int main()
{
    uint64_t N = 0;
    std::cin >> N;
    std::vector<std::vector<uint64_t>> gcds(N);
    uint64_t ones_quantity_in_input = 0;
    for (uint64_t index = 0; index < N; ++index)
    {
        uint64_t value = 0;
        std::cin >> value;
        if (value == 1)
        {
            ++ones_quantity_in_input;
        }
        if (ones_quantity_in_input == 0)
        {
            gcds[0].push_back(value);
        }
    }

    if (ones_quantity_in_input > 0)
    {
        std::cout << N - ones_quantity_in_input;
    }
    else
    {
        uint64_t level = get_coprime_gcds_level(gcds, N);
        if (level == 0)
        {
            std::cout << "-1";
        }
        else
        {
            std::cout << N + level - 1;
        }
    }

    return 0;
}
