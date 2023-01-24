#include <cassert>
#include <climits>
#include <iostream>


struct town_t
{
    int value = 0;
    long long result = INT_MAX;
};


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    town_t **towns = new town_t *[N];
    for (int i = 0; i < N; ++i)
    {
        towns[i] = new town_t[M];
        for (int j = 0; j < M; ++j)
        {
            std::cin >> towns[i][j].value;
        }
        towns[i][0].result = towns[i][0].value;
    }

    for (int j = 1; j < M; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int k = i - 1; k <= i + 1; ++k)
            {
                if ((k >= 0) && (k < N) && (towns[i][j].result > towns[k][j - 1].result))
                {
                    towns[i][j].result = towns[k][j - 1].result;
                }
            }
            towns[i][j].result += towns[i][j].value;
        }
    }

    int result = INT_MAX;
    int num = 0;
    for (int i = 0; i < N; ++i)
    {
        if (result > towns[i][M - 1].result)
        {
            result = towns[i][M - 1].result;
            num = i;
        }
    }
    int *history = new int[M];
    history[M - 1] = num + 1;
    for (int j = M - 2; j >= 0; --j)
    {
        int temp = 0;
        for (int k = num + 1; k >= num - 1; --k)
        {
            if ((k >= 0) && (k < N) && (towns[num][j + 1].result - towns[num][j + 1].value == towns[k][j].result))
            {
                temp = k;
                history[j] = k + 1;
            }
        }
        num = temp;
    }
    
    for (int i = 0; i < M; ++i)
    {
        std::cout << history[i] << " ";
    }
    std::cout << std::endl << result;
    
    for (int i = 0; i < N; ++i)
    {
        delete [] towns[i];
    }
    delete [] towns;
    
    return 0;
}