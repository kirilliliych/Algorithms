#include <cassert>
#include <climits>
#include <iostream>
 

int main()
{
	int N = 0;
    int M = 0;
	std::cin >> N >> M;
 
	int *axis = new int[N];
	for (int i = 0; i < N; ++i)
    {
	    std::cin >> axis[i];
    }

    int **dp = new int *[M];
    for (int i = 0; i < M; ++i)
    {
        dp[i] = new int[N];
    }

	int **pochtas = new int *[M];
    for (int i = 0; i < M; ++i)
    {
        pochtas[i] = new int[N];
    }
 
	for (int i = 0; i < N; ++i)
    {
		for (int j = 0; j < i; j++)
        {
			dp[0][i] += axis[i] - axis[j];
        }
    }
 
	long long sum_of_distances = 0;

	for (int i = 1; i < M; ++i)
    {
		for (int j = i + 1; j < N; ++j)
		{
			dp[i][j] = INT_MAX;

			for (int k = 0; k < j; ++k)
			{
				sum_of_distances = dp[i - 1][k];

				for (int l = k + 1; l < j; ++l)
                {
					sum_of_distances += std::min(axis[l] - axis[k], axis[j] - axis[l]);
                }
                
				if (dp[i][j] > sum_of_distances)
				{
					dp[i][j] = sum_of_distances;

					pochtas[i][j] = k;
				}
			}
		}
    }
 
	int pochta_place = 0;
	long long min_sum = INT_MAX;

	for (int i = M - 1; i < N; ++i)
	{
		sum_of_distances = dp[M - 1][i];
		for (int j = i + 1; j < N; ++j)
        {
			sum_of_distances += axis[j] - axis[i];
        }

		if (min_sum > sum_of_distances)
		{
			min_sum = sum_of_distances;

			pochta_place = i;
		}
	}

    int *buffer = new int[M];
    buffer[0] = axis[pochta_place]; 

	for (int i = M - 1; i > 0; --i) 
    {
        pochta_place = pochtas[i][pochta_place];
        buffer[M - i] = axis[pochta_place];
	}
 
        std::cout << min_sum << std::endl;
        for (int i = M - 1; i >= 0; --i)
        {
            std::cout << buffer[i] << " ";
        }

    delete [] buffer;
 
    for (int i = 0; i < M; ++i)
    {
        delete [] dp[i];
        delete [] pochtas[i];
    }
    delete [] dp;
    delete [] pochtas;

    delete [] axis;

	return 0;
}