#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>


const int MAX_EDGE_WEIGHT = 10;


long long dijkstra(int start_index, int end_index, const std::vector<std::vector<std::pair<int, int>>> &graph, int vertices_quantity)
{
    std::vector<int> distances(vertices_quantity, INT_MAX);
    distances[start_index] = 0;
    std::priority_queue<std::pair<int, int>> q{};
    q.push(std::make_pair(distances[start_index], start_index));

    bool ended = false; 
    while (!q.empty())
    {
        if (ended)
        {
            break;
        }

        int cur_distance_neg = -q.top().first;
        int cur_vertex_index =  q.top().second;
        q.pop();

        if (cur_distance_neg <= distances[cur_vertex_index])
        {
            for (int i = 0; i < graph[cur_vertex_index].size(); ++i)
            {
                int next_vertex_index = graph[cur_vertex_index][i].first;
                int weight            = graph[cur_vertex_index][i].second;

                if (distances[cur_vertex_index] + weight < distances[next_vertex_index])
                {
                    distances[next_vertex_index] = distances[cur_vertex_index] + weight;

                    if (next_vertex_index == end_index)
                    {
                        ended = true;

                        break;
                    }

                    q.push(std::make_pair(-distances[next_vertex_index], next_vertex_index));
                }
            }
        }
    }

    return distances[end_index];
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    std::vector<std::vector<std::pair<int, int>>> graph{(unsigned) N};
    std::vector<int[3]> edges{(unsigned) M};
    for (int i = 0; i < M; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        int weight = 0;
        std::cin >> v1 >> v2 >> weight;
        edges[i][0] = v1 - 1;
        edges[i][1] = v2 - 1;
        edges[i][2] = weight;
        graph[v1 - 1].push_back({v2 - 1, weight});
        graph[v2 - 1].push_back({v1 - 1, weight});
    }

    long long min_cycle = INT_MAX;
    for (int i = 0; i < M; ++i)
    {
        int cur_beginning = edges[i][0];
        int cur_ending    = edges[i][1];
        int cur_weight    = edges[i][2];

        
        graph[cur_beginning].erase(std::find(graph[cur_beginning].begin(), 
                                             graph[cur_beginning].end(),
                                             std::make_pair(cur_ending, cur_weight)));
        graph[cur_ending].erase(std::find(graph[cur_ending].begin(),
                                          graph[cur_ending].end(),
                                          std::make_pair(cur_beginning, cur_weight)));
        
        min_cycle = std::min(min_cycle, dijkstra(cur_beginning, cur_ending, graph, N) + cur_weight);

        graph[cur_beginning].push_back(std::make_pair(cur_ending, cur_weight));
        graph[cur_ending].push_back(std::make_pair(cur_beginning, cur_weight));
    }

    std::cout << min_cycle;

    return 0;
}