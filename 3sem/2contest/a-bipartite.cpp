#include <cassert>
#include <iostream>


template<class T>
class FastQueue 
{
private:

    T *body     = nullptr; 
    T *begin    = nullptr; 
    T *end      = nullptr; 
    T *body_end = nullptr;

public:

    FastQueue(size_t size) 
    {
        body  = new T[size];
        begin = end = body;

        body_end = body + size;
    }

    ~FastQueue() 
    { 
        delete[] body; 
    }

    void enqueue(const T &el) 
    { 
        *end = el;

        ++end;
    }

    bool empty() const 
    { 
        return begin == end;
    }

    T dequeue()
    { 
        ++begin;

        return *(begin - 1);
    }
};

struct Vertex
{
    int bfs_color  = 0;
    int part_color = 0;
    int index      = 0;
};


bool is_bipartite(bool **graph, size_t vertices_quantity)
{
    assert(graph != nullptr);

    Vertex *vertices = new Vertex[vertices_quantity];
    for (size_t i = 0; i < vertices_quantity; ++i)
    {
        vertices[i].index = i;
    }
    vertices[0].bfs_color  = 1;
    vertices[0].part_color = 1;
    FastQueue<Vertex> q{vertices_quantity};
    q.enqueue(vertices[0]);
    
    while (!q.empty())
    {
        Vertex cur_vertex = q.dequeue();
        for (size_t vertex_index = 0; vertex_index < vertices_quantity; ++vertex_index)
        {
            if (graph[cur_vertex.index][vertex_index])
            {
                if (cur_vertex.part_color == vertices[vertex_index].part_color)
                {
                    return false;
                }

                vertices[vertex_index].part_color = ((cur_vertex.part_color == 1) ? 2 : 1);

                if (vertices[vertex_index].bfs_color == 0)
                {
                    vertices[vertex_index].bfs_color = 1;
                    q.enqueue(vertices[vertex_index]);
                }
            }

            
        }

        cur_vertex.bfs_color = 2;
    }

    delete [] vertices;

    return true;
}

int main()
{
    size_t N = 0;
    size_t M = 0;
    std::cin >> N >> M;

    bool **graph = new bool *[N];
    for (int i = 0; i < N; ++i)
    {
        graph[i] = new bool[N];
        for (int j = 0; j < N; ++j)
        {
            graph[i][j] = false;
        }
    }

    for (int i = 0; i < M; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        std::cin >> v1 >> v2;

        graph[v1][v2] = true;
        graph[v2][v1] = true;
    }

    if (is_bipartite(graph, N))
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }

    for (int i = 0; i < N; ++i)
    {
        delete [] graph[i];
    }
    delete [] graph;

    return 0;
}