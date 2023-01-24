#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>


enum DFSColor
{
    WHITE,
    GREY,
    BLACK
};


struct Vertex
{
    DFSColor color_ = WHITE;
    std::vector<bool> adj_{};
    bool mark = true;
};


const size_t MAX_STR_SIZE = 1000000;


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    char encr_str[N + 1] = {};
    size_t encr_str_size = 0;

    std::vector<Vertex> vertices{(unsigned) N};
    for (int i = 0; i < N; ++i)
    {
        vertices[i].adj_.resize(N);
    }

    char word1[MAX_STR_SIZE] = {};
    char word2[MAX_STR_SIZE] = {};
    fgets(word1, MAX_STR_SIZE, stdin);
    fgets(word1, MAX_STR_SIZE, stdin);
    for (int i = 0; i < M - 1; ++i)
    {
        size_t word1_size = 0;
        size_t word2_size = 0;

        if (i % 2 == 0)
        {
            fgets(word2, MAX_STR_SIZE, stdin);
        }
        else
        {
            fgets(word1, MAX_STR_SIZE, stdin);
        }

        //std::cout << "word1 is " << word1;
        //std::cout << "word2 is " << word2;

        word1_size = strlen(word1) - 1;
        word2_size = strlen(word2) - 1;
        //std::cout << "word1_size is " << word1_size << std::endl;
        //std::cout << "word2_size is " << word2_size << std::endl;   

        int first_difference = 0;
        while ((first_difference < word1_size) && 
               (first_difference < word2_size) && 
               (word1[first_difference] == word2[first_difference]))
        {
            ++first_difference;
        }
        if ((first_difference >= word1_size) ||
            (first_difference >= word2_size))
        {
            //std::cout << "out of bounds!" << std::endl;
            continue;
        }
        //std::cout << "difference in " << first_difference << "th symbol" << std::endl;
        //std::cout << "word1[" << first_difference << "] is " << word1[first_difference] << std::endl;
        //std::cout << "word2[" << first_difference << "] is " << word2[first_difference] << std::endl;

        int smaller_letter_index = i % 2 == 0 ? word1[first_difference] - 'A' : 
                                                word2[first_difference] - 'A';
        int bigger_letter_index  = i % 2 == 0 ? word2[first_difference] - 'A' :
                                                word1[first_difference] - 'A';
        //vertices[smaller_letter_index].adj_.push_back(&vertices[bigger_letter_index]);
        vertices[smaller_letter_index].adj_[bigger_letter_index] = true;
        //std::cout << "added edge from " << smaller_letter_index << " to " << bigger_letter_index << std::endl;
    }

        // for (int i = 0; i < N; ++i)
        // {
        //     std::cout << "vertice " << i << ": " << std::endl;
        //     for (int j = 0; j < vertices[i].adj_.size(); ++j)
        //     {
        //         if (vertices[i].adj_[j])
        //         {
        //             std::cout << j << " ";
        //         }
        //     }
        //     std::cout << std::endl;
        // }

                                // std::stack<Vertex *> stk{};
                                // for (int i = 0; i < N; ++i)
                                // {
                                //     if (vertices[i].color_ != WHITE)
                                //     {
                                //         continue;
                                //     }

                                //     stk.push(&vertices[i]);

                                //     //size_t prev_encr_str_size = encr_str_size;
                                //     while (!stk.empty())
                                //     {
                                //         Vertex *cur_vertex = stk.top();
                                //         //stk.pop();
                                //         cur_vertex->color_ = GREY;

                                //         if (cur_vertex->mark)
                                //         {
                                //             cur_vertex->mark = false;
                                //             for (int i = 0; i < cur_vertex->adj_.size(); ++i)
                                //             {
                                //                 if ((cur_vertex->adj_[i]) && (vertices[i].color_ == WHITE))
                                //                 {
                                //                     stk.push(&vertices[i]);
                                //                 }
                                //             }
                                //         }
                                //         else
                                //         {
                                //             stk.pop();
                                //             cur_vertex->color_ = BLACK;
                                //             encr_str[encr_str_size] = 'A' + (cur_vertex - &vertices[0]);
                                //             ++encr_str_size;
                                //         }
                                //     }

                                //     //std::cout << "prev: " << prev_encr_str_size << " copy " << encr_str_size << std::endl;  
                                //     // size_t encr_str_size_copy = encr_str_size - 1;
                                //     // while (prev_encr_str_size < encr_str_size_copy)
                                //     // {
                                //     //     std::swap(encr_str[prev_encr_str_size], encr_str[encr_str_size_copy]);

                                //     //     ++prev_encr_str_size;
                                //     //     --encr_str_size_copy;
                                //     // }
                                // }


                                // for (int i = N - 1; i >= 0; --i)
                                // {
                                //     putchar(encr_str[i]);
                                // }

    char pool[N]     = {};
    size_t pool_size = 0;
    bool letters[N]  = {}; 
    while (pool_size != N)
    {
        for (int i = 0; i < N; ++i)
        {
            if (letters[i])
            {
                continue;
            }

            bool next_deleted = true;
            for (int j = 0; j < N; ++j)
            {
                if ((letters[j]) || (j == i))
                {
                    continue;
                }

                if (vertices[j].adj_[i])
                {
                    next_deleted = false;
                    
                    break;
                }
            }

            if (next_deleted)
            {
                letters[i] = true;
                printf("%c", 'A' + i);
            }
        }

        ++pool_size;
    }

    return 0;
}