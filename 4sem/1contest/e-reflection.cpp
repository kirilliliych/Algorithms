#include <cassert>
#include <iostream>
#include <vector>


std::vector<int> positions_in_front_of_mirror(const std::vector<int> &colors)
{
    std::vector<int> answer{};

    int colors_size = static_cast<int> (colors.size());
    std::vector<int> palindromes_in_position(colors_size, 0);

    int big_palindrom_left_index  = 0;
    int big_palindrom_right_index = -1;

    for (int i = 0; i < colors_size; ++i)
    {
        int cur_palindrom_size = 0;
        if (i <= big_palindrom_right_index)
        {
            cur_palindrom_size = std::min(big_palindrom_right_index - i + 1,
                                          palindromes_in_position[big_palindrom_right_index - i + big_palindrom_left_index + 1]);
        }
        
        bool answer_added = false;
        if (cur_palindrom_size >= colors_size - i)
        {
            answer.push_back(i);
            answer_added = true;
        }
        while ((i + cur_palindrom_size < colors_size) &&
               (i - cur_palindrom_size > 0)           &&
               (colors[i - cur_palindrom_size - 1] == colors[i + cur_palindrom_size])) 
        {
            ++cur_palindrom_size;

            if ((cur_palindrom_size == colors_size - i) && (!answer_added))
            {
                answer.push_back(i);
                answer_added = true;
            }
        }

        palindromes_in_position[i] = cur_palindrom_size;

        if (i + cur_palindrom_size - 1 > big_palindrom_right_index)
        {
            big_palindrom_left_index  = i - cur_palindrom_size;
            big_palindrom_right_index = i + cur_palindrom_size - 1;
        }
    }

    return answer;
}


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;
    std::vector<int> colors(N, 0);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> colors[i];
    }

    std::vector<int> answer = positions_in_front_of_mirror(colors);
    for (size_t i = 0; i < answer.size(); ++i)
    {
        std::cout << answer[i] << " ";
    }
    std::cout << N << std::endl;

    return 0;
}
