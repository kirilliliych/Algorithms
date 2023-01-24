#include <cassert>
#include <cstdlib>
#include <iostream>
#include <queue>



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


int main()
{
    int N = 0;
    int M = 0;
    int K = 0;
    std::cin >> N >> M >> K;
    
    bool *received = new bool[N * M];

    //std::queue<int *> q{};
    FastQueue<bool *> q{(unsigned) (N * M)};
    for (int i = 0; i < K; ++i)
    {
        int x = 0;
        int y = 0;
        std::cin >> y >> x;

        received[y * M + x] = true;
        //q.push(&received[y * M + x]);
        q.enqueue(&received[y * M + x]);
    }

    int cur_round = 0;

    int cur_round_actions_quantity = 0;
    while (!q.empty())
    {
        if (cur_round_actions_quantity == 0)
        {
            cur_round_actions_quantity = q.size();

            ++cur_round;

            //std::cout << "new round!" << std::endl << std::endl;
        }

        bool *received_ptr = q.dequeue();

        int index   = received_ptr - received;
        int x_index = index % M;
        int y_index = index / M;
        //std::cout << "cur elem is [" << y_index << "][" << x_index << "]" << std::endl; 

        int where_to_spread[8] = {(int)  x_index,
                                  (int) (y_index - 1),
                                  (int) (x_index - 1),
                                  (int)  y_index,
                                  (int) (x_index + 1),
                                  (int)  y_index,
                                  (int)  x_index,
                                  (int) (y_index + 1)
                                 };
        for (int i = 0; i < 4; ++i)
        {
            int x = where_to_spread[2 * i];
            int y = where_to_spread[2 * i + 1];
            if ((0 <= x) && (x < M) &&
                (0 <= y) && (y < N) &&
                (!received[y * M + x]))
            {
                received[y * M + x] = true;
                //q.push(&received[y * M + x]);
                q.enqueue(&received[y * M + x]);

                //std::cout << "pushed [" << y << "][" << x << "]" << std::endl;
            }
        }

        --cur_round_actions_quantity;
    }

    std::cout << cur_round - 1;

    delete [] received;

    return 0;
}