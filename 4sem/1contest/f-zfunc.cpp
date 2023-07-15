#include <cassert>
#include <iostream>
#include <vector>

const size_t kAlphabetSize = 26;


std::vector<int> prefix_from_z_func(std::vector<int> &z_func)
{
    size_t z_func_size = z_func.size();
    std::vector<int> prefixes(z_func_size, 0);

    for (size_t i = 1; i < z_func_size; ++i)
    {
        for (size_t j = z_func[i]; j > 0; --j)
        {
            if (prefixes[i + j - 1] > 0)
            {
                break;
            }

            prefixes[i + j - 1] = j;
        }
    }

    return prefixes;
}

std::vector<char> MinString(std::vector<int> &prefixes) {
    size_t str_size = prefixes.size();
    std::vector<char> answer(str_size, 0);

    for (size_t i = 0; i < str_size; ++i) {
        if (prefixes[i] == 0) {
            std::vector<bool> alphabet(kAlphabetSize, false);
            int index = i;
            while (index > 0) {
                index = prefixes[index - 1];
                alphabet[answer[index] - 'a'] = true;
            }
            int alphabet_index = 0;
            while (alphabet[alphabet_index]) {
                ++alphabet_index;
            }
            answer[i] = alphabet_index + 'a';

        } else {
            answer[i] = answer[prefixes[i] - 1];
        }
    }

    return answer;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> z_func(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> z_func[i];
    }
    std::vector<int> prefixes = prefix_from_z_func(z_func);
    std::vector<char> result = MinString(prefixes);
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i];
    }

    return 0;
}