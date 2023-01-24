#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>


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


enum BFSColor
{
    WHITE, 
    GREY,
    BLACK
};

struct Vertex
{
    BFSColor bfs_color = WHITE;
    bool covered = false;
};


void enqueue_adjacent_white_vertices(FastQueue<Vertex *> &q, std::vector<Vertex> &vertices, const Vertex *cur_vertex, int height, int width)
{
    assert(cur_vertex != nullptr);
    assert(height > 0);
    assert(width > 0);

    long long max_index = height * width;

    int cur_vertex_index = cur_vertex - &vertices[0];
    int offset_arr[4] = { cur_vertex_index - width,
                         (cur_vertex_index - 1) / width == (cur_vertex_index) / width ? cur_vertex_index - 1 : -1,
                         (cur_vertex_index + 1) / width == (cur_vertex_index) / width ? cur_vertex_index + 1 : -1,
                          cur_vertex_index + width
                        };
    
    for (int i = 0; i < 4; ++i)
    {
        if ((offset_arr[i] >= 0) && (offset_arr[i] < max_index) && 
            (vertices[offset_arr[i]].bfs_color == WHITE) && 
            (vertices[offset_arr[i]].covered))
        {
            vertices[offset_arr[i]].bfs_color = GREY;
            q.enqueue(&vertices[offset_arr[i]]);
        }
    }
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    std::vector<Vertex> vertices{(size_t) (N * M)};
    int offset = 0;
    for (long long i = -1; i < N * (M + 1); ++i)
    {
        int cur_symb = fgetc(stdin);
        if (i == -1)
        {
            continue;
        }

        // std::cout << "read " << cur_symb << std::endl;
        switch (cur_symb)
        {
            case '.':
            {
                vertices[i - offset].covered = false;

                break;
            }
            
            case '+':
            {
                vertices[i - offset].covered = true;

                break;
            }

            default:
            {
                ++offset;

                break;
            }
        }
    }
    // std::cout << std::endl;
    // for (int i = 0; i < N; ++i)
    // {
    //     for (int j = 0; j < M; ++j)
    //     {
    //         char a = vertices[i * M + j].covered ? '+' : '.';
    //         std::cout << a;
    //     }
    //     std::cout << std::endl;
    // }

    size_t components_quantity = 0;

    FastQueue<Vertex *> q{(size_t) (N * M)};
    for (long long i = 0; i < N * M; ++i)
    {
        if ((!vertices[i].covered) || (vertices[i].bfs_color != WHITE))
        {
            continue;
        }

        //std::cout << "\t\t\tNEW COMPONENT" << std::endl;

        ++components_quantity;

        vertices[i].bfs_color = GREY;
        q.enqueue(&vertices[i]);

        while (!q.empty())
        {
            Vertex *cur_vertex = q.dequeue();
            //std::cout << "processing " << "[" << (cur_vertex - &vertices[0]) / M << "][" << (cur_vertex - &vertices[0]) % M << "]" << std::endl;
            enqueue_adjacent_white_vertices(q, vertices, cur_vertex, N, M);

            cur_vertex->bfs_color = BLACK;
        }
    }

    std::cout << components_quantity << std::endl;

    return 0;
}