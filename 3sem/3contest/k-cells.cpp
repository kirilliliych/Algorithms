#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>


float prim_mst_weight(const std::vector<std::vector<float>> &distances, const int start)
{
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> q{};
    int vertices_quantity = distances.size();                       // this line sounds cringe btw :/
    std::vector<bool> is_in_mst(vertices_quantity, false);
    float result = 0;

    is_in_mst[start] = true;
    for (int i = 0; i < distances[start].size(); ++i)
    {
        q.push(std::pair<float, int> {distances[start][i], i});
    }

    while (!q.empty())
    {
        std::pair<float, int> distance = q.top();
        q.pop();

        if (!is_in_mst[distance.second])
        {
            is_in_mst[distance.second] = true;

            if (result < distance.first)
            {
                result = distance.first;
            }

            for (int i = 0; i < distances[distance.second].size(); ++i)
            {
                if (!is_in_mst[i])
                {
                    q.push(std::pair<float, int> {distances[distance.second][i], i});
                }
            }
        }   
    }

    return result;
}


int main()
{
    int N = 0;
    std::cin >> N;

    std::vector<std::pair<int, int>> towers(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> towers[i].first >> towers[i].second;
    }
    
    std::vector<std::vector<float>> distances(N, std::vector<float> (N, 0));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            distances[i][j] = std::sqrt((towers[i].first  - towers[j].first)  * (towers[i].first  - towers[j].first) +  
                                        (towers[i].second - towers[j].second) * (towers[i].second - towers[j].second));
        }
    }

    std::cout << std::fixed << std::setprecision(4) << prim_mst_weight(distances, 0);

    return 0;
}