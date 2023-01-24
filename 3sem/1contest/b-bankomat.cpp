#include <assert.h>
#include <climits>
#include <iostream>

struct sum_t
{
    long long ways_quantity = 0;
    int prev_minimum_ways_quantity_index = -1;
};


const int VERY_LARGE_NUMBER = INT_MAX;


void NameRequiredBanknotes(sum_t *sums, size_t required_sum)
{
    assert(sums != nullptr);

    for (size_t index = required_sum; sums[index].prev_minimum_ways_quantity_index != -1; index = sums[index].prev_minimum_ways_quantity_index)
    {
        std::cout << index - sums[index].prev_minimum_ways_quantity_index << " ";
    }
}

long long ReceiveWaysNumber(sum_t *sums, int index)
{
    assert(sums != nullptr);

    if (index < 0)
    {
        return VERY_LARGE_NUMBER;
    }
    else if (index == 0)
    {
        return 0;
    }
    else
    {
        return sums[index].ways_quantity;
    }
}

int CountMinimumBanknotesQuantity(size_t *nominals, size_t N, sum_t *sums, size_t required_sum)
{
    assert(nominals != nullptr);
    assert(sums     != nullptr);

    for (size_t i = 1; i <= required_sum; ++i)
    {
        sums[i].ways_quantity = VERY_LARGE_NUMBER;
        for (size_t j = 0; j < N; ++j)
        {
            int prev_minimum_ways_quantity_index = i - nominals[j];
            if (ReceiveWaysNumber(sums, prev_minimum_ways_quantity_index) + 1 < sums[i].ways_quantity)
            {
                sums[i].ways_quantity = ReceiveWaysNumber(sums, prev_minimum_ways_quantity_index) + 1;
                sums[i].prev_minimum_ways_quantity_index = prev_minimum_ways_quantity_index;
            }
        }
    }

    return sums[required_sum].ways_quantity == VERY_LARGE_NUMBER ? -1 : sums[required_sum].ways_quantity;
}

void DumpSumsArray(sum_t *array, size_t size)
{
    assert(array != nullptr);

    for (int i = 0; i < size; ++i)
    {
        std::cout << "(" << i << ", " << array[i].ways_quantity << ", " << array[i].prev_minimum_ways_quantity_index << ") ";
    }
    std::cout << std::endl;
}

int main()
{
    size_t N = 0;
    std::cin >> N;

    size_t *nominals = new size_t[N];
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> nominals[i];
    }

    size_t required_sum = 0;
    std::cin >> required_sum;

    sum_t *sums = new sum_t[required_sum + 1];
    long long result = CountMinimumBanknotesQuantity(nominals, N, sums, required_sum);
    std::cout << result << std::endl;
    if (result != -1)
    {
        NameRequiredBanknotes(sums, required_sum);
    }

    delete [] sums;

    delete [] nominals;

    return 0;
}