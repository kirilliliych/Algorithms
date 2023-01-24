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
    DFSColor color_              = WHITE;
    long long index_             = -1;
    long long depth_             = -1;
    long long highest_reachable_ = -1;
    std::vector<long long> adj_{};
};

struct JunctionsArr
{
    bool *junctions_ = nullptr;
    size_t size_  = 0;
};


void dfs_junction(long long cur_vertex_index, long long parent_index, JunctionsArr *arr, std::vector<Vertex> &vertices, long long *timer)
{
    assert(cur_vertex_index > 0);
    assert(arr   != nullptr);
    assert(timer != nullptr);

    vertices[cur_vertex_index].color_ = GREY;
    vertices[cur_vertex_index].depth_ = vertices[cur_vertex_index].highest_reachable_ = *timer;
    ++(*timer);

    long long root_children = 0;
    for (long long i = 0; i < vertices[cur_vertex_index].adj_.size(); ++i)
    {
        long long next_vertex_index = vertices[cur_vertex_index].adj_[i];
        if (next_vertex_index == parent_index)
        {
            continue;
        }

        if (vertices[next_vertex_index].color_ == GREY)
        {
            vertices[cur_vertex_index].highest_reachable_ = std::min(vertices[cur_vertex_index].highest_reachable_,
                                                                     vertices[next_vertex_index].depth_);
        }
        else
        {
            dfs_junction(next_vertex_index, cur_vertex_index, arr, vertices, timer);
            vertices[cur_vertex_index].highest_reachable_ = std::min(vertices[cur_vertex_index].highest_reachable_,
                                                                     vertices[next_vertex_index].highest_reachable_);

            if ((vertices[next_vertex_index].highest_reachable_ >= vertices[cur_vertex_index].depth_) && (parent_index != -1))
            {
                if (!arr->junctions_[cur_vertex_index])
                {
                    ++arr->size_;
                }
                arr->junctions_[cur_vertex_index] = true;
                
            }

            ++root_children;
        }
    }

    if ((parent_index == -1) && (root_children > 1))
    {
        if (!arr->junctions_[cur_vertex_index])
                {
                    ++arr->size_;
                }
                arr->junctions_[cur_vertex_index] = true;
    }
}


int comparator(const void *val1, const void *val2)
{
    assert(val1 != nullptr);
    assert(val2 != nullptr);

    return *(reinterpret_cast<const long long *> (val1)) - *(reinterpret_cast<const long long *> (val2)) <  0 ? -1 : 
           *(reinterpret_cast<const long long *> (val1)) - *(reinterpret_cast<const long long *> (val2)) == 0 ?  0 : 
                                                                                                                 1;
}


int main()
{
    long long N = 0;
    long long M = 0;
    std::cin >> N >> M;

    std::vector<Vertex> vertices{(unsigned) (N + 1)};
    for (long long i = 0; i < N + 1; ++i)
    {
        vertices[i].index_ = i;
    }
    for (long long i = 0; i < M; ++i)
    {
        long long v1 = 0;
        long long v2 = 0;
        std::cin >> v1 >> v2;

        vertices[v1].adj_.push_back(v2);
        vertices[v2].adj_.push_back(v1);
    }

    long long timer = 0;
    JunctionsArr arr{};
    arr.junctions_ = new bool[N + 1];
    for (int i = 0; i < N + 1; ++i)
    {
        arr.junctions_[i] = false;
    }
    for (long long i = 1; i < N + 1; ++i)
    {
        if (vertices[i].color_ != WHITE)
        {
            continue;
        }

        dfs_junction(i, -1, &arr, vertices, &timer);
    }

    std::cout << arr.size_ << std::endl;
    for (long long i = 1; i < N + 1; ++i)
    {
        if (arr.junctions_[i])
        {
            std::cout << i << " ";
        }
    }

    free(arr.junctions_);

    return 0;
}