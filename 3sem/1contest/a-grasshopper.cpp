#include <iostream>


#define aboba  std::cout << "aboba " << __LINE__ << std::endl;  


long long WaysToStairNumber(long long stair_number, size_t max_jump_height)
{
    if (stair_number <= 0)
    {
        return 1;
    }
    
    long long ways_quantity = 0;
    for (size_t jump_height = 1; jump_height <= max_jump_height && jump_height <= stair_number; ++jump_height)
    {
        ways_quantity += WaysToStairNumber(stair_number - jump_height, max_jump_height);
    }

    return ways_quantity;
}


int main()
{
    long long N = 0;
    size_t    M = 0;
    std::cin >> N >> M;
    
    std::cout << WaysToStairNumber(N, M);

    return 0;
}