#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>


long long dijkstra(const std::vector<std::vector<std::pair<int, int>>> &transitions, const int start, const int end)
{
    std::vector<long long> min_distances(transitions.size(), INT_MAX);
    min_distances[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q{};
    q.push({0, start});
    
    while (!q.empty())
    {
        std::pair<int, int> cur_pair = q.top();
        int cur_vertex_index = cur_pair.second;
        q.pop();

        for (int i = 0; i < transitions[cur_vertex_index].size(); ++i)
        {
            int distance_to_connected_vertex = transitions[cur_vertex_index][i].first;
            int connected_vertex_index       = transitions[cur_vertex_index][i].second;

            if (min_distances[connected_vertex_index] > min_distances[cur_vertex_index] + distance_to_connected_vertex)
            {
                min_distances[connected_vertex_index] = min_distances[cur_vertex_index] + distance_to_connected_vertex;
                q.push({min_distances[connected_vertex_index], connected_vertex_index});
            }
        }
    }

    return min_distances[end];
}


int main()
{
    int N = 0;
    int M = 0;
    int K = 0;
    std::cin >> N >> M >> K;

    std::vector<int> fires(K);
    for (int i = 0; i < K; ++i)
    {
        std::cin >> fires[i];
        --fires[i];
    }

    std::vector<std::vector<std::pair<int, int>>> tonnels(N);
    for (int i = 0; i < M; ++i)
    {
        int end1   = 0;
        int end2   = 0;
        int length = 0;
        std::cin >> end1 >> end2 >> length;
        tonnels[end1 - 1].push_back(std::pair<int, int> {length, end2 - 1});
        tonnels[end2 - 1].push_back(std::pair<int, int> {length, end1 - 1});
    }

    int S = 0;
    int F = 0;
    std::cin >> S >> F;
    --S;
    --F;

    long long exit_time = dijkstra(tonnels, S, F);
    bool fail = false;
    for (int i = 0; i < fires.size(); ++i)
    {
        long long res = dijkstra(tonnels, fires[i], F);
        if (dijkstra(tonnels, fires[i], F) <= exit_time)
        {
            fail = true;
            std::cout << "-1";
            
            break;
        }
    }

    if (!fail)
    {
        std::cout << exit_time;
    }
    
    return 0;
}