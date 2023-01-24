#include <cassert>
#include <iostream>
#include <climits>
#include <vector>


#define aboba std::cout << "aboba " << __LINE__ << std::endl;

class DSU
{
public:
//---------------------------------------------------------
    DSU(int capacity)
      : cur_components_quantity_(capacity),
        capacity_(capacity),
        height_(std::vector<int>(capacity, -1)),
        parent_ref_(std::vector<int>(capacity, -1))
    {}

    ~DSU() = default;
//---------------------------------------------------------
    int find(int index) const
    {
        return parent_ref_[index] == -1 ? index : find(parent_ref_[index]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return;
        }

        if (height_[x] < height_[y])
        {
            parent_ref_[x] = y;
        }
        else
        {
            parent_ref_[y] = x;
            if (height_[x] == height_[y])
            {
                ++height_[x];
            }
        }

        --cur_components_quantity_;
    }

    int get_components_quantity() const
    {
        return cur_components_quantity_;
    }
//---------------------Variables---------------------------
private:

    int cur_components_quantity_ = 0;
    int capacity_ = 0;
    std::vector<int> height_{};
    std::vector<int> parent_ref_{};
};


std::vector<int> calc_components(std::vector<std::vector<int>> &edges, std::vector<std::pair<int, int>> &destroyed, int bunkers_quantity, int requests_quantity)
{
    assert(bunkers_quantity  > -1);
    assert(requests_quantity > -1);

    DSU graph(bunkers_quantity);
    for (int i = 0; i < edges.size(); ++i)
    {
        for (int j = 0; j < edges[i].size(); ++j)
        {
            bool is_deleted = false;
            for (int k = 0; k < destroyed.size(); ++k)
            {
                int v1 = destroyed[k].first;
                int v2 = destroyed[k].second;
                
                if (((i == v1) && (edges[i][j] == v2)) || ((i == v2) && (edges[i][j] == v1)))
                {
                    is_deleted = true;

                    break;
                }
            }
            if (is_deleted)
            {
                continue;
            }
            graph.unite(i, edges[i][j]);
        }
    }

    std::vector<int> components_quantity(requests_quantity + 1);
    components_quantity[requests_quantity] = graph.get_components_quantity();
    for (int i = 0; i < requests_quantity; ++i)
    {
        graph.unite(destroyed[i].first, destroyed[i].second);
        components_quantity[requests_quantity - 1 - i] = graph.get_components_quantity(); 
    }

    return components_quantity;
}


int main()
{
    int V = 0;
    int E = 0;
    int M = 0;
    std::cin >> V >> E >> M;

    std::vector<std::vector<int>> edges(V);
    for (int i = 0; i < E; ++i)
    {
        int b1 = 0;
        int b2 = 0;
        std::cin >> b1 >> b2;
        edges[b1].push_back(b2);
        edges[b2].push_back(b1);
    }

    std::vector<std::pair<int, int>> destroyed(M);
    for (int i = 0; i < M; ++i)
    {
        int b1 = 0;
        int b2 = 0;
        std::cin >> b1 >> b2;
        destroyed[M - 1 - i] = {b1, b2};
    }
    
    std::vector<int> result = calc_components(edges, destroyed, V, M);
    for (int i = 0; i < result.size(); ++i)
    {
        std::cout << result[i] << std::endl;
    }

    return 0;
}