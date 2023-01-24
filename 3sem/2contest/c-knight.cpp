#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
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
    Vertex *prev = NULL;
    int distance   = -1;
    std::vector<bool> adj{};
};


int get_min_path(std::vector<Vertex> &vertices, 
                 int x_beginning, int y_beginning,
                 int x_ending,    int y_ending,
                 int size, std::vector<Vertex *> &path)
{
    int start_index = y_beginning * size + x_beginning;
    int end_index   = y_ending    * size + x_ending;
    //std::cout << "start_index: " << start_index << " end_index: " << end_index << std::endl;

    bool ending_reached = false;
    FastQueue<Vertex *> q{size * size};

    vertices[start_index].distance  = 0;
    vertices[start_index].bfs_color = GREY;
    q.enqueue(&vertices[start_index]);
    while (!q.empty())
    {
        Vertex *cur_vertex = q.dequeue();
        for (int i = 0; i < cur_vertex->adj.size(); ++i)
        {
            if (cur_vertex->adj[i])
            {   //std::cout << cur_vertex - &vertices[0] << " is adj to " << i << std::endl;
                if (vertices[i].bfs_color == WHITE)
                {
                    vertices[i].distance   = cur_vertex->distance + 1;
                    vertices[i].prev       = cur_vertex;
                    vertices[i].bfs_color  = GREY;

                    if (i == end_index)
                    {
                        ending_reached = true;

                        Vertex *vertex_ptr = &vertices[i];
                        while (vertex_ptr->prev != NULL)
                        {
                            path.push_back(vertex_ptr);

                            vertex_ptr = vertex_ptr->prev;
                        }

                        return vertices[i].distance;
                    }
                    q.enqueue(&vertices[i]);
                    //std::cout << "pushed " << i << std::endl;
                }
            }
        }

        cur_vertex->bfs_color = BLACK;
    }
}


void str_to_coords(const char *str, int *x, int *y)
{
    assert(str != nullptr);
    assert(x   != nullptr);
    assert(y   != nullptr);

    *x = str[0] - 'A';
    *y = atoi(str + 1) - 1;
}

int main()
{
    int N = 0;
    char input[4] = {};
    std::cin >> N >> input;
    int x_beginning = 0;
    int y_beginning = 0;
    str_to_coords(input, &x_beginning, &y_beginning);
    std::cin >> input;
    int x_ending = 0;
    int y_ending = 0;
    str_to_coords(input, &x_ending, &y_ending);

    std::vector<Vertex> vertices{N * N};
    for (int i = 0; i < N * N; ++i)
    {
        int cur_x = i % N;
        int cur_y = i / N;
        
        vertices[i].adj.resize(N * N);
        for (int j = 0; j < N * N; ++j)
        {
            int attacked_x = j % N;
            int attacked_y = j / N;
        
            vertices[i].adj[j] = (((attacked_x == cur_x - 2) && (attacked_y == cur_y - 1)) ||
                                  ((attacked_x == cur_x - 2) && (attacked_y == cur_y + 1)) ||
                                  ((attacked_x == cur_x + 2) && (attacked_y == cur_y - 1)) ||
                                  ((attacked_x == cur_x + 2) && (attacked_y == cur_y + 1)) ||
                                  ((attacked_x == cur_x - 1) && (attacked_y == cur_y - 2)) ||
                                  ((attacked_x == cur_x - 1) && (attacked_y == cur_y + 2)) ||
                                  ((attacked_x == cur_x + 1) && (attacked_y == cur_y - 2)) ||
                                  ((attacked_x == cur_x + 1) && (attacked_y == cur_y + 2))
                                ) ?
            true : false;
        }
    }

    std::vector<Vertex *> path{};
    int result = get_min_path(vertices, x_beginning, y_beginning,
                                        x_ending,    y_ending,
                                        N, path);
    std::cout << result << std::endl;
    std::reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); ++i)
    {
        char x = (path[i] - &vertices[0]) % N + 'A';
        int  y = (path[i] - &vertices[0]) / N + 1;
        std::cout << x << y << std::endl;
        //std::cout << path[i] - &vertices[0] << " ";
    }
    std::cout << std::endl;

    return 0;
}