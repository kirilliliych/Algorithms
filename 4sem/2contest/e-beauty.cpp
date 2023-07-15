#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>


std::vector<size_t> delete_to_reach_such_beauty(size_t ceil)
{
    std::vector<bool> is_present(ceil, true);
    std::vector<size_t> result(ceil / 2);
    result[ceil / 2 - 1] = 0;
    for (size_t cur_beauty = ceil / 2 - 1; cur_beauty > 0; --cur_beauty)
    {
        result[cur_beauty - 1] = result[cur_beauty];
        for (size_t value_to_extract = 2 * (cur_beauty + 1); value_to_extract <= ceil; value_to_extract += (cur_beauty + 1))
        {
            if (is_present[value_to_extract - 1])
            {
                is_present[value_to_extract - 1] = false;
                ++result[cur_beauty - 1];
            }
        }
    }

    return result;
}


int main()
{
    size_t n = 0;
    size_t q = 0;
    scanf("%ld %ld", &n, &q);

    std::vector<size_t> delete_to_reach_beauty = delete_to_reach_such_beauty(n);
    auto begin = delete_to_reach_beauty.begin();
    for (size_t i = 0; i < q; ++i)
    {
        size_t input = 0;
        scanf("%ld", &input);

        auto place = std::lower_bound(delete_to_reach_beauty.begin(),
                                       delete_to_reach_beauty.end(),
                                        n - input,
                                       std::greater<size_t> ());

        printf("%ld ", place - begin + 1);
    }

    return 0;
}