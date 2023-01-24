#include <cassert>
#include <iostream>
#include <vector>


bool kun(int cur_index, std::vector<std::vector<int>> &matrix,
                        std::vector<bool> &is_used, 
                        std::vector<int> &from_left_matching_right)
{
    if (is_used[cur_index])
    {
        return false;
    }

    is_used[cur_index] = true;
    for (int i = 0; i < matrix[cur_index].size(); ++i)
    {
        int next_index = matrix[cur_index][i];
        if ((from_left_matching_right[next_index] == -1) ||
            (kun(from_left_matching_right[next_index],
                 matrix, is_used, from_left_matching_right)))
        {
            from_left_matching_right[next_index] = cur_index;

            return true; 
        }
    }

    return false;
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    std::vector<std::vector<int>> matrix{(unsigned) N};
    for (int i = 0; i < M; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        std::cin >> v1 >> v2;
        matrix[v1 - 1].push_back(v2 - 1);
    }

    int answer = 0;
    std::vector<int> from_left_matching_right{N};
    from_left_matching_right.assign(N, -1);
    for (int i = 0; i < N; ++i)
    {
        //std::cout << "i " << i << std::endl;
        std::vector<bool> is_used(N, false);
        if (kun(i, matrix, is_used, from_left_matching_right))
        {
            ++answer;
        }
        // for (int j = 0; j < N; ++j)
        // {
        //     std::cout << from_left_matching_right[j] << " ";
        // }
        // std::cout << std::endl;
    }

    std::cout << N - answer;

    return 0;
}