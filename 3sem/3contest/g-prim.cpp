#include <cassert>
#include <iostream>
#include <queue>
#include <vector>


long long prim_mst_weight(const std::vector<std::vector<std::pair<int, int>>> &edges, const int start)
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q{};
    int vertices_quantity = edges.size();                       // this line sounds cringe btw :/
    std::vector<bool> is_in_mst(vertices_quantity, false);
    long long result = 0;

    is_in_mst[start] = true;
    for (int i = 0; i < edges[start].size(); ++i)
    {
        q.push(edges[start][i]);
    }
    
    int isolated_vertices = vertices_quantity - 1;
    while ((isolated_vertices >= 0) && !q.empty())
    {
        std::pair<int, int> min_weight_edge = q.top();
        q.pop();

        if (!is_in_mst[min_weight_edge.second])
        {
            is_in_mst[min_weight_edge.second] = true;

            --isolated_vertices;
            result += min_weight_edge.first;

            for (int i = 0; i < edges[min_weight_edge.second].size(); ++i)
            {
                q.push(edges[min_weight_edge.second][i]);
            }
        }   
    }

    return result;
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    std::vector<std::vector<std::pair<int, int>>> edges(N);
    for (int i = 0; i < M; ++i)
    {
        int end1   = 0;
        int end2   = 0;
        int weight = 0;
        std::cin >> end1 >> end2 >> weight;

        edges[end1 - 1].push_back(std::pair<int, int> {weight, end2 - 1});
        edges[end2 - 1].push_back(std::pair<int, int> {weight, end1 - 1});
    }

    std::cout << prim_mst_weight(edges, 0);

    return 0;
}