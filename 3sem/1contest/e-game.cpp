#include <cassert>
#include <cmath>
#include <iostream>


int main()
{
    int N = 0;
    std::cin >> N;

    bool *winner = new bool[N + 1];
    bool if_won = false;
    winner[0] = false;
    winner[1] = true;
    for (long long i = 2; i < N + 1; ++i)
    {
        long long rounded = (long long) (sqrt((double) i));

        for (long long j = 1; j <= rounded; ++j)
        {
            if (winner[i - j] == false)
            {
                winner[i] = true;

                break;
            }


        }
    }

    if (winner[N] == false)
    {
        std::cout << "Second";
    }
    else
    {
        std::cout << "First";
    }

    delete [] winner;

    return 0;
}