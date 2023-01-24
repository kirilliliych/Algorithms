#include <cassert>
#include <iostream>
#include <queue>
#include <vector>


long long prim_mst_weight(const std::vector<std::vector<std::pair<int, int>>> &edges, const int start)
{
    std::priority_queue<std::pair<int, int>> q{};
    int vertices_quantity = edges.size();                       // this line sounds cringe btw :/
    std::vector<bool> is_in_mst(vertices_quantity, false);
    long long result = 0;

    is_in_mst[start] = true;
    for (int i = 0; i < edges[start].size(); ++i)
    {
        q.push(edges[start][i]);
    }
    
    while (!q.empty())
    {
        std::pair<int, int> max_weight_edge = q.top();
        q.pop();

        if (!is_in_mst[max_weight_edge.second])
        {
            is_in_mst[max_weight_edge.second] = true;
            result += max_weight_edge.first;

            for (int i = 0; i < edges[max_weight_edge.second].size(); ++i)
            {
                q.push(edges[max_weight_edge.second][i]);
            }
        }   
    }

    return result;
}


int main()
{
    int N = 0;
    std::cin >> N;

    std::vector<std::vector<std::pair<int, int>>> edges(N);
    for (int i = 0; i < N * N; ++i)
    {
        int weight = 0;
        std::cin >> weight;
        if (weight == 0)
        {
            continue;
        }

        edges[i % N].push_back(std::pair<int, int> {weight, i / N});
        edges[i / N].push_back(std::pair<int, int> {weight, i % N});
    }

    std::cout << prim_mst_weight(edges, 0);

    return 0;
}