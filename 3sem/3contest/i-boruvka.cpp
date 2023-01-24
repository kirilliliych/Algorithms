#include <cassert>
#include <iostream>
#include <climits>
#include <vector>


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


long long boruvka(std::vector<std::vector<std::pair<int, int>>> &edges, int vertices_quantity, int edges_quantity)
{
    assert(vertices_quantity > -1);
    assert(edges_quantity    > -1);

    DSU graph(vertices_quantity);
    long long mst_weight = 0;

    while (graph.get_components_quantity() > 1)
    {
        std::vector<std::pair<int, int>> min_edge(vertices_quantity, {INT_MAX, INT_MAX});

        for (int i = 0; i < edges.size(); ++i)
        {
            for (int j = 0; j < edges[i].size(); ++j)
            {
                int v1 = i;
                int v2 = edges[i][j].first;
                int leader1 = graph.find(v1);
                int leader2 = graph.find(v2);
                if (leader1 == leader2)
                {
                    continue;
                }
                int weight = edges[i][j].second;

                if ((min_edge[leader1].second > weight) || ((min_edge[leader1].second == weight) && (min_edge[leader1].first > v2)))
                {
                    min_edge[leader1] = std::pair<int, int>(v2, weight); 
                }

                if ((min_edge[leader2].second > weight) || ((min_edge[leader2].second == weight) && (min_edge[leader2].first > v1)))
                {
                    min_edge[leader2] = std::pair<int, int>(v1, weight);
                }
            }
        }

        for (int i = 0; i < vertices_quantity; ++i)
        {
            if (min_edge[i].first == INT_MAX)
            {
                continue;
            }

            if (graph.find(i) == graph.find(min_edge[i].first))
            {
                continue;
            }

            graph.unite(i, min_edge[i].first);
            mst_weight += min_edge[i].second;
        }
    }

    return mst_weight;
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;
    
    std::vector<std::vector<std::pair<int, int>>> edges(N);
    for (int i = 0; i < M; ++i)
    {
        int begin  = 0;
        int end    = 0;
        int weight = 0;
        std::cin >> begin >> end >> weight;
        edges[begin - 1].push_back({end - 1, weight});
    }

    std::cout << boruvka(edges, N, M);

    return 0;
}