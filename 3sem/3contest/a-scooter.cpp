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
    std::cin >> N >> M;
    std::vector<std::vector<int>> heights(N, std::vector<int>());
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            int cur_height = 0;
            std::cin >> cur_height;
            heights[i].push_back(cur_height);
        }
    }

    std::vector<std::vector<std::pair<int, int>>> transitions(N * M);
    for (int i = 0; i < N * M; ++i)
    {
        transitions.push_back(std::vector<std::pair<int, int>>());
        int y = i / M;
        int x = i % M;

        std::vector<std::pair<int, int>> offsets{{x - 1, y}, {x, y - 1}, {x, y + 1}, {x + 1, y}};
        for (int j = 0; j < offsets.size(); ++j)
        {
            int cur_x = offsets[j].first;
            int cur_y = offsets[j].second;
            if ((0 <= cur_x) && (cur_x < M) &&
                (0 <= cur_y) && (cur_y < N))
            {
                int dist = std::max(heights[cur_y][cur_x] - heights[y][x], 0);
                transitions[i].push_back(std::pair<int, int>{dist, cur_y * M + cur_x});
            }
        }
    }

    std::cout << dijkstra(transitions, 0, N * M - 1);
    
    return 0;
}