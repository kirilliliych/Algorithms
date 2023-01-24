#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>


enum Color
{
    WHITE,
    GREY,
    BLACK
};


struct Vertex
{
    Color color_  = WHITE;
    int distance_ = -1;
    std::vector<Vertex *>adj_{};
};


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

    size_t size() const
    {
        return end - begin;
    }
};


void fill_adj(std::vector<Vertex> &conditions, int biggest_flask_capacity, 
                                               int smaller_flask_capacity, 
                                               int smallest_flask_capacity)
{
    assert(biggest_flask_capacity  > 0);
    assert(smaller_flask_capacity  > 0);
    assert(smallest_flask_capacity > 0);

    int multiplier = smaller_flask_capacity + 1;
    for (int i = 0; i < biggest_flask_capacity + 1; ++i)
    {
        for (int j = 0; j < smaller_flask_capacity + 1; ++j)
        {
            int smallest_flask_content = biggest_flask_capacity - i - j;
            if (smallest_flask_content > smallest_flask_capacity)
            {
                continue;
            }

            if (i > 0)
            {
                if (j < smaller_flask_capacity)
                {
                    int transfused = std::min(i, smaller_flask_capacity - j);
                    conditions[i * multiplier + j].adj_.push_back(&conditions[(i - transfused) * multiplier + (j + transfused)]);
                }

                if (smallest_flask_content < smallest_flask_capacity)
                {
                    int transfused = std::min(i, smallest_flask_capacity - smallest_flask_content);
                    conditions[i * multiplier + j].adj_.push_back(&conditions[(i - transfused) * multiplier + j]);
                }
            }

            if (j > 0)
            {
                if (i < biggest_flask_capacity)
                {
                    int transfused = std::min(j, biggest_flask_capacity - i);
                    conditions[i * multiplier + j].adj_.push_back(&conditions[(i + transfused) * multiplier + (j - transfused)]);
                }

                if (smallest_flask_content < smallest_flask_capacity)
                {
                    int transfused = std::min(j, smallest_flask_capacity - smallest_flask_content);
                    conditions[i * multiplier + j].adj_.push_back(&conditions[i * multiplier + (j - transfused)]);
                }
            }

            if (smallest_flask_content > 0)
            {
                if (i < biggest_flask_capacity)
                {
                    int transfused = std::min(smallest_flask_content, biggest_flask_capacity - i);
                    conditions[i * multiplier + j].adj_.push_back(&conditions[(i + transfused) * multiplier + j]);
                }

                if (j < smaller_flask_capacity)
                {
                    int transfused = std::min(smallest_flask_content, smaller_flask_capacity - j);
                    conditions[i * multiplier + j].adj_.push_back(&conditions[i * multiplier + (j + transfused)]);
                }
            }
        }
    }
}


int main()
{
    int N = 0;
    int M = 0;
    int K = 0;
    int L = 0;
    std::cin >> N >> M >> K >> L;
    if (M < K)
    {
        std::swap(M, K);
    }

    std::vector<Vertex> conditions{(unsigned) ((N + 1) * (M + 1))};
    fill_adj(conditions, N, M, K);

    FastQueue<Vertex *> q{(unsigned) ((N + 1) * (M + 1))};
    conditions[N * (M + 1)].distance_ = 0;
    conditions[N * (M + 1)].color_    = GREY;
    q.enqueue(&conditions[N * (M + 1)]);
    
    bool calculated = false;
    while (!q.empty())
    {
        if (calculated)
        {
            break;
        }
        
        Vertex *cur_condition = q.dequeue();
        //int a = cur_condition - &conditions[0];
        //int x = a / (M + 1);
        //int y = a % (M + 1);
        //int z = N - x - y;
        //std::cout << "cur condition is " << x << " " << y << " " << z << std::endl;
        for (int i = 0; i < cur_condition->adj_.size(); ++i)
        {
            Vertex *neighbour = cur_condition->adj_[i];
            if (neighbour->color_ == WHITE)
            {
                neighbour->distance_ = cur_condition->distance_ + 1;
                neighbour->color_    = GREY;
                q.enqueue(neighbour);

                int delta = neighbour - &conditions[0];
                if (delta / (M + 1) == L)
                {
                    calculated = true;
                    std::cout << neighbour->distance_;

                    break;
                }
            }
        }
    }
    if (!calculated)
    {
        std::cout << "OOPS";
    }

    return 0;
}