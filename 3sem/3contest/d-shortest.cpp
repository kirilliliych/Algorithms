#include <cassert>
#include <climits>
#include <iostream>
#include <vector>


struct dist_t
{
    long long dist = 0;
    bool changed = false;
};


dist_t *bellman_ford(const std::vector<std::vector<std::pair<int, int>>> &edges, const int N, const int start)
{
    dist_t *min_distances = new dist_t[N];
    for (int i = 0; i < N; ++i)
    {
        min_distances[i].dist = INT_MAX;
    }
    min_distances[start].dist = 0;
    min_distances[start].changed = true;
    
    for (int i = 0; i < N - 1; ++i)
    {
        for (int j = 0; j < edges.size(); ++j)
        {
            for (int k = 0; k < edges[j].size(); ++k)
            {
                if ((min_distances[j].changed) && (min_distances[j].dist + edges[j][k].first < min_distances[edges[j][k].second].dist))
                {
                    min_distances[edges[j][k].second].dist = min_distances[j].dist + edges[j][k].first;
                    min_distances[edges[j][k].second].changed = true;
                }
            }
        }
    }

    for (int j = 0; j < edges.size(); ++j)
    {
        for (int k = 0; k < edges[j].size(); ++k)
        {
            if ((min_distances[j].changed) && (min_distances[j].dist + edges[j][k].first < min_distances[edges[j][k].second].dist))
            {
                delete min_distances;

                return nullptr;
            }
        }
    }

    return min_distances;
}


int main()
{
    int N = 0;
    int M = 0;
    int S = 0;
    std::cin >> N >> M >> S;

    std::vector<std::vector<std::pair<int, int>>> edges(N);
    for (int i = 0; i < M; ++i)
    {
        int begin  = 0;
        int end    = 0;
        int weight = 0;
        std::cin >> begin >> end >> weight;
        edges[begin].push_back(std::pair<int, int> (weight, end));
    }

    dist_t *result = bellman_ford(edges, N, S);
    if (result == nullptr)
    {
        std::cout << "IMPOSSIBLE";
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            if (!result[i].changed)
            {
                std::cout << "UNREACHABLE";
            }
            else
            {
                std::cout << result[i].dist;
            }
            std::cout << " ";
        }

        delete result;
    }

    return 0;
}