#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>


uint64_t get_subsqrts_and_paired_quantity(uint64_t value)
{
    assert(value != 0);

    if (value == 1)
    {
        return 1;
    }

    uint64_t result = 2;
    uint64_t subsqrt = 2;
    for (subsqrt = 2; subsqrt * subsqrt < value; ++subsqrt)
    {
        result += 2;
    }
    if ((subsqrt - 1) * subsqrt > value)
    {
        --result;
    }
    else if (subsqrt * subsqrt == value)
    {
        ++result;
    }

    return result;
}

std::vector<uint64_t> get_subsqrts_and_paired(uint64_t value)
{
    assert(value != 0);

    uint64_t subsqrts_and_paired_quantity = get_subsqrts_and_paired_quantity(value);
    std::vector<uint64_t> subsqrts_and_paired(subsqrts_and_paired_quantity);
    subsqrts_and_paired[0] = 1;

    if (subsqrts_and_paired_quantity != 1)
    {
        subsqrts_and_paired[subsqrts_and_paired_quantity - 1] = value;
        uint64_t subsqrt_index = 1;
        uint64_t subsqrt = 2;
        for (subsqrt = 2; subsqrt * subsqrt <= value; ++subsqrt)
        {
            subsqrts_and_paired[subsqrt_index] = subsqrt;
            subsqrts_and_paired[subsqrts_and_paired_quantity - subsqrt_index - 1] = value / subsqrt;

            ++subsqrt_index;
        }

        subsqrts_and_paired.push_back(subsqrt - 1); // trunc(sqrt(value)) is in the last cell
    }

    return std::move(subsqrts_and_paired);
}

uint64_t get_correct_index(const std::vector<uint64_t> &vector, uint64_t threshold, uint64_t ceil, uint64_t value)
{
    return value <= threshold ? value - 1 : (vector.size() - 1) - ceil / value;
}

uint64_t get_primes_quantity(uint64_t ceil)
{
    std::vector<uint64_t> subsqrts_and_paired = get_subsqrts_and_paired(ceil);
    uint64_t size = subsqrts_and_paired.size() - 1;
    uint64_t trunc_sqrt = subsqrts_and_paired[size];   // last element is trunc(sqrt(ceil)), remember

    std::vector<uint64_t> dp(size);
    for (uint64_t i = 0; i < size; ++i)
    {
        dp[i] = subsqrts_and_paired[i];
    }

    uint64_t values_used_in_sieving = 0;
    for (uint64_t subsqrt = 2; subsqrt * subsqrt <= ceil; ++subsqrt)
    {
        if (dp[get_correct_index(subsqrts_and_paired, trunc_sqrt, ceil, subsqrt - 1)] !=
            dp[get_correct_index(subsqrts_and_paired, trunc_sqrt, ceil, subsqrt)])
        {
            ++values_used_in_sieving;

            for (uint64_t i = size; i > 0; --i)
            {
                if (subsqrts_and_paired[i - 1] < subsqrt * subsqrt)
                {
                    break;
                }

                dp[i - 1] -= dp[get_correct_index(subsqrts_and_paired, trunc_sqrt, ceil,
                                                  subsqrts_and_paired[i - 1] / subsqrt)] - values_used_in_sieving;
            }
        }
    }

    return dp[get_correct_index(subsqrts_and_paired, trunc_sqrt, ceil, ceil)] - 1;
}


int main()
{
    uint64_t n = 0;
    std::cin >> n;
    std::cout << get_primes_quantity(n);

    return 0;
}
