#include <cassert>
#include <climits>
#include <iostream>
#include <vector>


void floyd_warshall(std::vector<std::vector<long long>> &shortest_paths)
{
    int vertices_quantity = shortest_paths.size();
    for (int transit_vertex_max_index = 0; transit_vertex_max_index < vertices_quantity; ++transit_vertex_max_index)
    {
        for (int vertex_from_index = 0; vertex_from_index < vertices_quantity; ++vertex_from_index)
        {
            for (int vertex_to_index = 0; vertex_to_index < vertices_quantity; ++vertex_to_index)
            {
                shortest_paths[vertex_from_index][vertex_to_index] = std::min(shortest_paths[vertex_from_index][vertex_to_index],
                                                                              shortest_paths[vertex_from_index][transit_vertex_max_index] + 
                                                                              shortest_paths[transit_vertex_max_index][vertex_to_index]);
            }
        }
    }
}

int main()
{
    int N = 0;
    std::cin >> N;

    std::vector<std::vector<long long>> shortest_paths{};
    for (int i = 0; i < N; ++i)
    {
        std::vector<long long> new_row;
        shortest_paths.push_back(new_row);
        for (int j = 0; j < N; ++j)
        {
            int path_len = 0;
            std::cin >> path_len;
            if (path_len == -1)
            {
                path_len = INT_MAX;
            }
            shortest_paths[i].push_back(path_len);
        }
    }

    floyd_warshall(shortest_paths);

    long long max_shortest_path = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (shortest_paths[i][j] < INT_MAX)
            {
                max_shortest_path = std::max(max_shortest_path, shortest_paths[i][j]);
            }
        }
    }

    std::cout << max_shortest_path << std::endl;
}