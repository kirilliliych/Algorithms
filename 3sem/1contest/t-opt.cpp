#include <cassert>
#include <climits>
#include <iostream>


long long get_min_expenses(const int **conditions, int shops_quantity, int shop_characteristic)           // ATTENTION! products quantity INCLUDES travel cost(sic!)
{
    assert(conditions != nullptr);
    assert(shops_quantity > 0);
    assert(shop_characteristic > 1);

    int products_quantity = shop_characteristic - 1;                                                      // cuz first shop characteristic is travel cost

    long long ***dp = new long long **[2];                                                                // int *** looks kinda wtf, but 
    size_t products_tuples_quantity = 1 << products_quantity;                                             // 1 coord is about shops quantity,
    for (int i = 0; i < 2; ++i)                                                                           // 2 coord is about tuple of products
    {                                                                                                     // 3 coord is whether shop from 1 coord is visited or not
        dp[i] = new long long *[products_tuples_quantity];                                                // frankly speaking, usin' three * for the first time
        for (int j = 0; j < products_tuples_quantity; ++j)                                                // O_o <-(my face while writing this)
        {
            dp[i][j] = new long long[2];
        }
    }                                                                                                     

    for (int i = 0; i < shops_quantity; ++i)
    {
        dp[i % 2][0][1] = conditions[i][0];


        for (int j = 0; j < products_tuples_quantity; ++j)
        {
            if (i != 0)
            {
                dp[i % 2][j][0] = std::min(dp[(i + 1) % 2][j][0], dp[(i + 1) % 2][j][1]);
            }
            else
            {
                dp[i % 2][j][0] = j > 0 ? INT_MAX : 0;
            }

            dp[i % 2][j][1] = INT_MAX;
        }

        for (int j = 0; j < products_tuples_quantity; ++j)
        {
            for (int k = 0; k < products_quantity; ++k)
            {
                dp[i % 2][j | (1ull << k)][1] = std::min(dp[i % 2][j | (1ull << k)][1], dp[i % 2][j][0] + conditions[i][0] + conditions[i][k + 1]);
            }
        }

        for (int j = 0; j < products_tuples_quantity; ++j)
        {
            for (int k = 0; k < products_quantity; ++k)
            {
                dp[i % 2][j | (1ull << k)][1] = std::min(dp[i % 2][j | (1ull << k)][1], dp[i % 2][j][1] + conditions[i][k + 1]);
            }
        }
    }

    long long result = std::min(dp[(shops_quantity - 1) % 2][products_tuples_quantity - 1][0], dp[(shops_quantity - 1) % 2][products_tuples_quantity - 1][1]);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < products_tuples_quantity; ++j)
        {
            delete [] dp[i][j];
        }

        delete [] dp[i];
    }
    delete [] dp;

    return result;
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    int **characteristics = new int *[N];
    for (int i = 0; i < N; ++i)
    {
        characteristics[i] = new int[M + 1];

        for (int j = 0; j < M + 1; ++j)
        {
            std::cin >> characteristics[i][j];
        }
    }

    std::cout << get_min_expenses(const_cast<const int **> (characteristics), N, M + 1);

    for (int i = 0; i < N; ++i)
    {
        delete [] characteristics[i];
    }
    delete [] characteristics;

    return 0;
}