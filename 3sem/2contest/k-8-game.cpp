#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>


enum Color
{
    WHITE,
    GREY,
    BLACK
};


struct Vertex
{
    Vertex(){}

    Vertex(const char *state, int distance)
      : distance_(distance)
    {
        strcpy(state_, state);
    }

    char state_[10] = {};
    int distance_ = -1;
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



long long hash(const char *str)
{
    assert(str != nullptr);
    
    const char *ptr = str;
    long long hash  = 0;
    while (*ptr != '\0')
    {
        int val = *ptr - '0';
        hash = hash * 10 + val;

        ++ptr;
    }

    return hash;
}



int main()
{
    char start_state[10] = {};
    int read_cells = 0;
    while ((start_state[read_cells] = fgetc(stdin)) != EOF)
    {
        if ((('1' <= start_state[read_cells]) && (start_state[read_cells] <= '8')) ||
            (start_state[read_cells] == ' '))
        {
            if (start_state[read_cells] == ' ')
            {
                start_state[read_cells] = '9';
            }

            ++read_cells;
        }
    }
    start_state[9] = '\0';
    
    char canonic[10] = "123456789";
    
    int q_size = 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9;
    FastQueue<Vertex> q{(unsigned) q_size};
    q.enqueue(Vertex{start_state, 0});

    std::vector<char *> states{};

    std::unordered_map<int, const char *> prev_states{};
    long long key = hash(start_state);
    prev_states.insert({key, start_state});
    bool reached = false;
    while (!q.empty())
    {
        if (reached)
        {
            break;
        }

        Vertex cur_vertex = q.dequeue();
        //if (cnt < 10)
        //std::cout << "cur state is " << cur_vertex.state_ << std::endl;
        char *space_place = strchr(cur_vertex.state_, '9');
        assert(space_place != nullptr);
        int space_place_index = space_place - cur_vertex.state_;

        char *space_place_change[4] = { space_place - 3,
                                       (space_place - cur_vertex.state_) % 3 == 0 ? nullptr : space_place - 1,
                                       (space_place - cur_vertex.state_) % 3 == 2 ? nullptr : space_place + 1,
                                        space_place + 3
                                      };
        for (int i = 0; i < 4; ++i)
        {
            if ( (space_place_change[i] != nullptr)         &&
                ((space_place_change[i] - cur_vertex.state_) >= 0) &&
                ((space_place_change[i] - cur_vertex.state_) <  9))
            {
                char *new_state_ptr = new char[10];
                strcpy(new_state_ptr, cur_vertex.state_);

                int change_with_index = space_place_change[i] - cur_vertex.state_;
                char temp = new_state_ptr[change_with_index];
                new_state_ptr[change_with_index] = new_state_ptr[space_place_index];
                new_state_ptr[space_place_index] = temp;
                if (strncmp(new_state_ptr, canonic, 9) == 0)
                {
                    reached = true;
                    std::cout << cur_vertex.distance_ + 1;

                    break;
                }

                long long new_state_key = hash(new_state_ptr);
                if (prev_states.find(new_state_key) == prev_states.end())
                {
                    states.push_back(new_state_ptr);
                    prev_states.insert({new_state_key, new_state_ptr});
                    q.enqueue(Vertex{new_state_ptr, cur_vertex.distance_ + 1});
                }
            }
        }
    }

    if (!reached)
    {
        std::cout << "-1";
    }

    return 0;
}