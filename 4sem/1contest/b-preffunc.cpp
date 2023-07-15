#include <cassert>
#include <iostream>
#include <vector>


std::vector<char> min_string(std::vector<int> &prefixes)
{
    size_t str_size = prefixes.size();
    std::vector<char> answer(str_size);

    for (size_t i = 0; i < str_size; ++i)
    {
        if (prefixes[i] == 0)
        {
            std::vector<int> zero_prefixes_indices_for_forbidden_letters{};
            int index = i;
            while (index > 0)
            {
                index = prefixes[index - 1];
                zero_prefixes_indices_for_forbidden_letters.push_back(index);
            }
            char possible_new_letter_for_zero_prefix_position = 'a';
            for (size_t j = 0; j < zero_prefixes_indices_for_forbidden_letters.size(); ++j)
            {
                if (possible_new_letter_for_zero_prefix_position == answer[zero_prefixes_indices_for_forbidden_letters[i]])
                {
                    ++possible_new_letter_for_zero_prefix_position;
                }
            }

            answer[i] = possible_new_letter_for_zero_prefix_position;
        }
        else
        {
            answer[i] = answer[prefixes[i] - 1];
        }
    }

    return answer;
}


void main()
{
    int N = 0;
    std::cin >> N;
    std::vector<int> prefixes(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> prefixes[i];
    }

    std::vector<char> result = min_string(prefixes);
    for (size_t i = 0; i < result.size(); ++i)
    {
        std::cout << result[i];
    }

    return 0;
}
