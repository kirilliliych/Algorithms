#include <cassert>
#include <iostream>
#include <utility>
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
    int A = 0;
    int B = 0;
    std::cin >> N >> M >> A >> B;
    
    int pattern_cardinality = 0;
    char cur_symb = 0;
    std::vector<std::vector<bool>> field{N};
    for (int i = 0; i < N; ++i)
    {
        field[i].resize(M);
        for (int j = 0; j < M; ++j)
        {
            std::cin >> cur_symb;
            if (cur_symb == '*')
            {
                field[i][j] = true;

                ++pattern_cardinality;
            }
        }
    }

    if (2 * B <= A)
    {
        std::cout << pattern_cardinality * B << std::endl;

        return 0;
    }
    
    std::pair<int, int> plitka_position[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    std::vector<std::vector<int>> matrix{};
    int cur1x2 = 0;
    for (int i = 0; i < N; ++i)                                             // placing 1x2
    {
        for (int j = 0; j < M; ++j)
        {
            if (((i + j) % 2 == 0) && field[i][j])                          // looking only at even positions
            {
                matrix.push_back(std::vector<int>());
                for (int k = 0; k < 4; ++k)
                {
                    int new_i = i + plitka_position[k].first;
                    int new_j = j + plitka_position[k].second;
                    if ((new_i >= 0) && (new_i < N) &&
                        (new_j >= 0) && (new_j < M) &&
                        field[new_i][new_j])
                    {
                        matrix[cur1x2].push_back(new_i * M + new_j);
                    }
                }

                ++cur1x2;
            }
        }
    }

    int answer = 0;

    std::vector<int> from_left_matching_right{N * M};
    from_left_matching_right.assign(N * M, -1);

    for (int i = 0; i < cur1x2; ++i)
    {
        std::vector<bool> is_used{};
        is_used.resize(cur1x2);
        is_used.assign(cur1x2, false);
        if (kun(i, matrix, is_used, from_left_matching_right))
        {
            answer += A;
            pattern_cardinality -= 2;
        }
    }

    std::cout << answer + pattern_cardinality * B;
    
    return 0;
}