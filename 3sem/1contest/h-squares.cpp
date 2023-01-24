#include <climits>
#include <iostream>


int main()
{
    int N = 0;
    std::cin >> N;

    int *ways_quantity = new int[N + 1];
    ways_quantity[0] = 0;
    ways_quantity[1] = 1;
    for (int i = 2; i < N + 1; ++i)
    {   
        ways_quantity[i] = INT_MAX;
        int index = i - 1;
        for (int j = 1; index >= 0; j += 2, index -= j)
        {
            if (ways_quantity[i] > ways_quantity[index] + 1)
            {
                ways_quantity[i] = ways_quantity[index] + 1;
            }
        }
    }

    std::cout << ways_quantity[N];

    delete [] ways_quantity;

    return 0;
}