#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>


struct Airport
{
    int64_t x;
    int64_t y;
    int64_t flights;
};


namespace modulo
{
    const int64_t MODULO = 1e9 + 9; 
}

namespace matrices
{
    const std::vector<int64_t> FIBONACCI_MATRIX{0, 1, 1, 1};
    const std::vector<int64_t> ID_MATRIX{1, 0, 0, 1};
}


std::vector<int64_t> moduled_mult_matrices2x2(const std::vector<int64_t> &matrix1,
                                              const std::vector<int64_t> &matrix2,
                                              int64_t modulo)
{
    std::vector<int64_t> result(4); // 2x2=4
    result[0] = (matrix1[0] * matrix2[0] % modulo + matrix1[1] * matrix2[2] % modulo) % modulo;
    result[1] = (matrix1[0] * matrix2[1] % modulo + matrix1[1] * matrix2[3] % modulo) % modulo;
    result[2] = (matrix1[2] * matrix2[0] % modulo + matrix1[3] * matrix2[2] % modulo) % modulo;
    result[3] = (matrix1[2] * matrix2[1] % modulo + matrix1[3] * matrix2[3] % modulo) % modulo;

    return result;
}


std::vector<int64_t> get_matrix_pow(const std::vector<int64_t> &matrix, uint64_t deg)
{
    if (deg == 0)
    {
        return {0, 0};
    }
    if (deg == 1)
    {
        return matrix;
    }

    std::vector<int64_t> result = matrices::ID_MATRIX;
    std::vector<int64_t> base = matrix;

    while (deg > 0)
    {
        if (deg & 1)
        {
            std::vector<int64_t> prev_result = result;
            result = moduled_mult_matrices2x2(prev_result, base, modulo::MODULO);
        }

        std::vector<int64_t> prev_base = base;
        base = moduled_mult_matrices2x2(prev_base, prev_base, modulo::MODULO);

        deg >>= 1;
    }

    return result;
}

uint64_t get_ways_to_diag_quantity(const Airport &airport, uint64_t diag_coef)
{
    assert(airport.y - airport.x - diag_coef >= 0);

    uint64_t delta = airport.y - airport.x - diag_coef;
    std::vector<int64_t> fibonacci_matrix_deg = get_matrix_pow(matrices::FIBONACCI_MATRIX, delta);
    if ((fibonacci_matrix_deg[0] == 0) &&
        (fibonacci_matrix_deg[1] == 0))
    {
        return 1;
    }

    return fibonacci_matrix_deg[3];
}


int main()
{
    int n = 0;
    int q = 0;
    std::cin >> n >> q;
    
    std::vector<Airport> airports(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> airports[i].x >> airports[i].y >> airports[i].flights;
        airports[i].flights %= modulo::MODULO;
    }

    std::vector<int64_t> diags(q);
    for (int i = 0; i < q; ++i)
    {
        std::cin >> diags[i];
    }

    for (int diag_index = 0; diag_index < q; ++diag_index)
    {
        uint64_t result = 0;
        for (int airport_index = 0; airport_index < n; ++airport_index)
        {
            if (airports[airport_index].y - airports[airport_index].x - diags[diag_index] >= 0)
            {
                result += get_ways_to_diag_quantity(airports[airport_index], diags[diag_index]) % modulo::MODULO *
                          airports[airport_index].flights % modulo::MODULO;
                result %= modulo::MODULO;
            }
        }

        std::cout << result << std::endl;
    }

    return 0;
}
