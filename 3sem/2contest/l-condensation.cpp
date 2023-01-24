#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>
#include <vector>


enum DFSColor
{
    WHITE,
    GREY,
    BLACK
};


struct Vertex
{
    DFSColor dfs_color_ = WHITE;
    int color_ = -1;
    std::vector<Vertex *>adj_{};
};


void dfs_sort_by_tout(Vertex *cur_vertex, std::vector<Vertex *> &sorted_by_tout)
{
    assert(cur_vertex != nullptr);

    cur_vertex->dfs_color_ = GREY;
    for (int i = 0; i < cur_vertex->adj_.size(); ++i)
    {
        if (cur_vertex->adj_[i]->dfs_color_ == WHITE)
        {
            dfs_sort_by_tout(cur_vertex->adj_[i], sorted_by_tout);
        }
    }

    sorted_by_tout.push_back(cur_vertex);
}

void dfs_kosaraju_finish(Vertex *cur_vertex, int color_index)
{
    assert(cur_vertex != nullptr);

    cur_vertex->color_ = color_index;
    for (int i = 0; i < cur_vertex->adj_.size(); ++i)
    {
        if (cur_vertex->adj_[i]->color_ == -1)
        {
            dfs_kosaraju_finish(cur_vertex->adj_[i], color_index);
        }
    }
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    std::vector<Vertex *> sorted_by_tout{};
    std::set<std::pair<int, int>> condensed_edges{};
    std::vector<Vertex> vertices1{(unsigned) (N + 1)};
    std::vector<Vertex> vertices2{(unsigned) (N + 1)};

    for (int i = 0; i < M; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        std::cin >> v1 >> v2;
        vertices1[v1].adj_.push_back(&vertices1[v2]);
        vertices2[v2].adj_.push_back(&vertices2[v1]);
    }

    for (int i = 1; i < N + 1; ++i)
    {
        if (vertices1[i].dfs_color_ == WHITE)
        {
            dfs_sort_by_tout(&vertices1[i], sorted_by_tout);
        }
    }

    for (int i = 0; i < sorted_by_tout.size(); ++i)
    {
        int vertex_index = sorted_by_tout[i] - &vertices1[0];
        sorted_by_tout[i] = &vertices2[vertex_index];
    }

    int color_index = 0;
    for (int i = 0; i < N; ++i)
    {
        if (sorted_by_tout[(N - 1) - i]->color_ == -1)
        {
            dfs_kosaraju_finish(sorted_by_tout[(N - 1) - i], color_index);
        }

        ++color_index;
    }
    
    for (int i = 1; i < vertices2.size(); ++i)
    {
        for (int j = 0; j < vertices2[i].adj_.size(); ++j)
        {
            if (vertices2[i].color_ != vertices2[i].adj_[j]->color_)
            {
                condensed_edges.insert(std::make_pair(vertices2[i].color_, vertices2[i].adj_[j]->color_));
            }
        }
    }

    std::cout << condensed_edges.size();

    return 0;
}