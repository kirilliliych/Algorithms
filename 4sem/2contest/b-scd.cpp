#include <cassert>
#include <iostream>
#include <vector>


uint64_t get_composite_numbers_smallest_prime_divisors_sum(uint64_t upper_border)
{
    uint64_t result = 0;
    std::vector<uint64_t> smallest_prime_divisor(upper_border + 1, 0);
    std::vector<uint64_t> found_prime_numbers{};
    for (uint64_t cur_value = 2; cur_value <= upper_border; ++cur_value)
    {
        if (smallest_prime_divisor[cur_value] == 0)
        {
            smallest_prime_divisor[cur_value] = cur_value;
            found_prime_numbers.push_back(cur_value);
        }
        else
        {
            result += smallest_prime_divisor[cur_value];
        }
    
        for (uint64_t prime_index = 0; prime_index < found_prime_numbers.size()                              &&
                                       found_prime_numbers[prime_index] <= smallest_prime_divisor[cur_value] &&
                                       cur_value * found_prime_numbers[prime_index] <= upper_border; 
             ++prime_index)
        {
            smallest_prime_divisor[cur_value * found_prime_numbers[prime_index]] = found_prime_numbers[prime_index];
        }
    }

    return result;
}


int main()
{
    uint64_t N = 0;
    std::cin >> N;
    std::cout << get_composite_numbers_smallest_prime_divisors_sum(N);

    return 0;
}
