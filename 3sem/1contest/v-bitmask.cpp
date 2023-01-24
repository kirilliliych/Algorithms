#include <cassert>
#include <climits>
#include <iostream>
#include <unordered_map>


int calc_free_cells_quantity(size_t state, int height, int width, int *height_index, int *width_index)
{
    assert(height > 0);
    assert(width  > 0);
    assert(height_index != nullptr);
    assert(width_index  != nullptr);

    int result = 0;
    bool got_free_cell = false;
    for (int i = height - 1; i >= 0; --i)
    {
        for (int j = width - 1; j >= 0; --j)
        {
            if ((state & (1ull << (i * width + j))) == 0)
            {
                if (!got_free_cell)
                {
                    *height_index = i;
                    *width_index  = j; 

                    got_free_cell = true;
                }

                ++result;
            }
        }
    }

    return result;
}

long long pave_variants_quantity(std::unordered_map<size_t, size_t> &dp, size_t state, int height, int width)
{
    assert(height > 0);
    assert(width  > 0);

    if (dp.find(state) != dp.end())                                                                     // already calculated
    {
        return dp[state];
    }

    int free_height_index = 0;
    int free_width_index  = 0;
    int free_cells_quantity = calc_free_cells_quantity(state, height, width, &free_height_index, &free_width_index);

//---------------------------MULTIPLE CASES YEAAAAAAAAH <333333-----1000-7--------
    if (free_cells_quantity <= 1)                                                                       // can't place and mask even invalid
    {
        dp[state] = 0;
        
        return dp[state];
    }

    if (free_height_index >= 1)                                                                         // 2x1
    {
        if ((state & (1ull << ((free_height_index - 1) * width + free_width_index))) == 0)
        {
            if (free_cells_quantity == 2)
            {
                dp[state] = 1;

                return dp[state];
            }
            else
            {
                dp[state] += pave_variants_quantity(dp, state + (1ull <<  (free_height_index      * width + free_width_index)) +
                                                                (1ull << ((free_height_index - 1) * width + free_width_index)),
                                                    height, width);
            }
        }
    }

    if (free_height_index >= 2)                                                                        // 3x1
    {
        if (((state & (1ull << ((free_height_index - 1) * width + free_width_index))) == 0) && 
            ((state & (1ull << ((free_height_index - 2) * width + free_width_index))) == 0))
        {
            if (free_cells_quantity == 3)
            {
                dp[state] = 1;

                return dp[state];
            }
            else
            {
                dp[state] += pave_variants_quantity(dp, state + (1ull <<  (free_height_index      * width + free_width_index)) +
                                                                (1ull << ((free_height_index - 1) * width + free_width_index)) + 
                                                                (1ull << ((free_height_index - 2) * width + free_width_index)),
                                                    height, width);
            }
        }
    }

    if (free_width_index >= 1)                                                                         // 1x2
    {
        if ((state & (1ull << (free_height_index * width + free_width_index - 1))) == 0)
        {
            if (free_cells_quantity == 2)
            {
                dp[state] = 1;

                return dp[state];
            }
            else
            {
                dp[state] += pave_variants_quantity(dp, state + (1ull << (free_height_index * width + free_width_index)) +
                                                                (1ull << (free_height_index * width + free_width_index - 1)),
                                                    height, width);
            }
        }
    }

    if (free_width_index >= 2)                                                                         // 1x3
    {
        if (((state & (1ull << (free_height_index * width + free_width_index - 1))) == 0) &&
            ((state & (1ull << (free_height_index * width + free_width_index - 2))) == 0))
        {
            if (free_cells_quantity == 3)
            {
                dp[state] = 1;

                return dp[state];
            }
            else
            {
                dp[state] += pave_variants_quantity(dp, state + (1ull << (free_height_index * width + free_width_index))     +
                                                                (1ull << (free_height_index * width + free_width_index - 1)) +
                                                                (1ull << (free_height_index * width + free_width_index - 2)),
                                                    height, width);
            }
        }
    }

    return dp[state];
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;
    if (N < M)
    {
        std::swap(N, M);
    }

    std::unordered_map<size_t, size_t> dp;
    std::cout << pave_variants_quantity(dp, 0, N, M);

    return 0;
}