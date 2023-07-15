#include <cassert>
#include <iostream>
#include <vector>


const char SEPARATOR = '#';


std::vector<size_t> CalculatePrefixes(std::string &str) {
    size_t str_size = str.size();
    std::vector<size_t> prefixes(str_size, 0);
    prefixes[0] = 0;
    for (size_t i = 1; i < str_size; ++i) {
        int possible_border_length = prefixes[i - 1];
        while ((possible_border_length > 0) && (str[i] != str[possible_border_length])) {
            possible_border_length = prefixes[possible_border_length - 1];
        }
        prefixes[i] = str[i] == str[possible_border_length] ? possible_border_length + 1 : possible_border_length;
    }

    return prefixes;
}

std::vector<bool> get_interestingness(std::vector<size_t> &prefixes)
{
    size_t prefixes_size = prefixes.size();
    std::vector<bool> sections(prefixes_size + 1, false);                               // needa last element for yes/no
    for (size_t i = 0; i < prefixes_size - 1; ++i)
    {
        if ((prefixes[i] == 0) && (prefixes[i + 1] == 0))
        {
            sections[prefixes_size] = true;
            
            break;
        }

        if (prefixes[i] > prefixes[i + 1])
        {
            sections[i + 1 - prefixes[i + 1]] = true;
        }
    }

    sections[prefixes_size - 1] = true;

    return sections;
}


template<typename T>
std::vector<size_t> get_subvector(std::vector<T> &v, size_t start, size_t size)
{
    std::vector<T> subvector(size);
    for (size_t i = 0; i < size; ++i)
    {
        subvector[i] = v[start + i]; 
    }

    return subvector;
}


int main()
{
    std::string fiona_word  = "";
    std::string donkey_word = "";
    std::cin >> fiona_word >> donkey_word;

    std::string concatenated = fiona_word + SEPARATOR + donkey_word;
    size_t fiona_word_size   = fiona_word.size();
    size_t donkey_word_size  = donkey_word.size();
    std::vector<size_t> prefixes = CalculatePrefixes(concatenated);    
    size_t donkey_word_in_concatenated_start_index = fiona_word_size + 1;

    std::vector<size_t> prefixes_for_donkey_word = get_subvector(prefixes, donkey_word_in_concatenated_start_index,
                                                                 donkey_word_size);
    std::vector<bool> result = get_interestingness(prefixes_for_donkey_word);
    if (result[donkey_word_size])                                                           // remember we have additional indicator element at the end
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No" << std::endl;

        size_t cur_part_start = 0;
        for (size_t i = 0; i < donkey_word_size; ++i)
        {
            if (result[i])
            {
                for (size_t j = cur_part_start; j <= i; j++)
                {
                    std::cout << donkey_word[j];
                }
                std::cout << " ";

                cur_part_start = i + 1;
            }
        }
    }

    return 0;
}
