#include <cassert>
#include <climits>
#include <iostream>
#include <stack>
#include <vector>


void dfs(int init_index, int N, const std::vector<std::vector<short>> &existing_map,
                                      std::vector<std::vector<bool>> &result_map)
{
    std::vector<bool> used(N, false);
    std::stack<int> s{};
    s.push(init_index);

    while (!s.empty())
    {
        int cur_index = s.top();
        s.pop();
        used[cur_index] = true;

        for (int i = 0; i < existing_map[cur_index].size(); ++i)
        {
            int next = existing_map[cur_index][i];
            result_map[init_index][next] = true;
            if (!used[existing_map[cur_index][i]])
            {
                s.push(existing_map[cur_index][i]);
                
            }
        }
    }
}


int main()
{
    int N = 0;
    std::cin >> N;

    std::vector<std::vector<short>> existing_map{};
    for (int i = 0; i < N; ++i)
    {
        std::vector<short> new_line{};
        existing_map.push_back(new_line);
        for (int j = 0; j < N; ++j)
        {
            char symb = 0;
            std::cin >> symb;
            if (symb == '1')
            {
                existing_map[i].push_back(j);
            }
        }

        if (i != N - 1)
        {
            getchar();
        }
    }

    std::vector<std::vector<bool>> result_map(N, std::vector<bool>(N, false));
    for (int i = 0; i < N; ++i)
    {
        dfs(i, N, existing_map, result_map);
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << result_map[i][j];
        }
        std::cout << std::endl;
    }
}