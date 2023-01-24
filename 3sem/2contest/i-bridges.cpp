#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>


enum DFSColor
{
    WHITE,
    GREY,
    BLACK
};


struct Vertex
{
    DFSColor color_        = WHITE;
    int index_             = -1;
    int depth_             = -1;
    int highest_reachable_ = -1;
    std::vector<Vertex *> adj_{};
};

struct Edge
{
    Edge(int v1, int v2)
      : v1_(v1),
        v2_(v2)
    {}

    int v1_      = -1;
    int v2_      = -1;
    bool bridge_ = false;
};

struct BridgesArr
{
    int *bridges_ = nullptr;
    size_t size_  = 0;

    void add(int value)
    {
        bridges_[size_++] = value;
    }

    size_t size() const
    {
        return size_;
    }
};


void dfs_bridge(Vertex *cur_vertex, Vertex *parent_vertex, const std::vector<Edge> &edges, BridgesArr *arr)
{
    assert(cur_vertex    != nullptr);
    assert(arr           != nullptr);
    assert(arr->bridges_ != nullptr);

    //std::cout << "cur_vertex_index: " << cur_vertex->index_ << std::endl;
    cur_vertex->color_ = GREY;
    cur_vertex->depth_ = cur_vertex->highest_reachable_ = parent_vertex == nullptr ?
                                                          0 :
                                                          parent_vertex->depth_ + 1;
    //std::cout << "cur_vertex_depth: " << cur_vertex->depth_ << std::endl;
    for (int i = 0; i < cur_vertex->adj_.size(); ++i)
    {
        if (cur_vertex->adj_[i] != parent_vertex)
        {
            if (cur_vertex->adj_[i]->color_ == GREY)
            {
                cur_vertex->highest_reachable_ = std::min(cur_vertex->highest_reachable_, cur_vertex->adj_[i]->depth_);
            }
            else
            {
                dfs_bridge(cur_vertex->adj_[i], cur_vertex, edges, arr);
                cur_vertex->highest_reachable_ = std::min(cur_vertex->highest_reachable_, cur_vertex->adj_[i]->highest_reachable_);
                if (cur_vertex->depth_ < cur_vertex->adj_[i]->highest_reachable_)
                {
                    for (int j = 0; j < edges.size(); ++j)
                    {
                        if (((cur_vertex->index_          == edges[j].v1_) &&
                             (cur_vertex->adj_[i]->index_ == edges[j].v2_))     ||
                            ((cur_vertex->index_          == edges[j].v2_) &&
                             (cur_vertex->adj_[i]->index_ == edges[j].v1_)))
                        {
                            arr->add(j + 1);

                            break;
                        }
                    }
                }
            }
        }
    }
}


int comparator(const void *val1, const void *val2)
{
    assert(val1 != nullptr);
    assert(val2 != nullptr);

    return *(reinterpret_cast<const int *> (val1)) - *(reinterpret_cast<const int *> (val2)) <  0 ? -1 : 
           *(reinterpret_cast<const int *> (val1)) - *(reinterpret_cast<const int *> (val2)) == 0 ?  0 : 
                                                                                                     1;
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    std::vector<Vertex> vertices{(unsigned) (N + 1)};
    for (int i = 0; i < N + 1; ++i)
    {
        vertices[i].index_ = i;
    }
    std::vector<Edge> edges{};
    for (int i = 0; i < M; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        std::cin >> v1 >> v2;

        vertices[v1].adj_.push_back(&vertices[v2]);
        vertices[v2].adj_.push_back(&vertices[v1]);

        edges.push_back(Edge(v1, v2));
    }


    BridgesArr arr{};
    arr.bridges_ = new int[M];
    for (int i = 1; i < N + 1; ++i)
    {
        if (vertices[i].color_ != WHITE)
        {
            continue;
        }

        dfs_bridge(&vertices[i], nullptr, edges, &arr);
    }

    std::cout << arr.size() << std::endl;
    qsort(arr.bridges_, arr.size(), sizeof(int), comparator);
    for (int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr.bridges_[i] << std::endl;
    }

    free(arr.bridges_);

    return 0;
}