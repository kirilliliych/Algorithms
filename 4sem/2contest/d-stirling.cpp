#include <sys/types.h>
#include <cassert>
#include <iostream>
#include <vector>


namespace modulo
{
    const int64_t MODULO = 1e9 + 7;
}


int64_t moduled_mult(int64_t op1, int64_t op2, int64_t modulo)
{
    return (op1 % modulo) * (op2 % modulo) % modulo;
}


int64_t bin_pow(int64_t base, int64_t deg)
{
    int64_t result = 1;
    while (deg > 0)
    {
        if (deg & 1)
        {
            result = moduled_mult(result, base, modulo::MODULO);
        }

        base = moduled_mult(base, base, modulo::MODULO);
        deg >>= 1;
    }

    return result;
}

int64_t get_inverse(int64_t base, int64_t modulo)
{
    return bin_pow(base, modulo - 2);
}


int64_t get_combination_number(int64_t n, int64_t k, const std::vector<int64_t> &factorial,
                                                     const std::vector<int64_t> &inverse_factorial)
{
    assert(k <= n);
    assert(k >= 0);

    if (k == 0)
    {
        return 1;
    }

    return moduled_mult(factorial[n],
                        moduled_mult(inverse_factorial[n - k], inverse_factorial[k], modulo::MODULO),
                        modulo::MODULO);
}

int64_t get_stirling(int64_t n, int64_t k, const std::vector<int64_t> &factorial,
                                           const std::vector<int64_t> &inverse_factorial)
{
    if (n == 0)
    {
        return k == 0;
    }
    if (k == 0)
    {
        return n == 0;
    }

    int64_t answer = 0;
    for (int64_t index = 0; index < k; ++index)
    {
        int64_t to_add = moduled_mult(get_combination_number(k, index, factorial, inverse_factorial),
                                      bin_pow(k - index, n), modulo::MODULO);
        if (index % 2 == 1)
        {
            to_add *= modulo::MODULO - 1;
            to_add %= modulo::MODULO;
        }
        answer += to_add;
    }

    return moduled_mult(answer, inverse_factorial[k], modulo::MODULO);
}


int64_t get_stirling_sum(int64_t n, int64_t k, const std::vector<int64_t> &factorial,
                                               const std::vector<int64_t> &inverse_factorial)
{
    return (get_stirling(n, k, factorial, inverse_factorial) +
            (n - 1) * get_stirling(n - 1, k, factorial, inverse_factorial) % modulo::MODULO) % modulo::MODULO;
}


int main()
{
    int64_t n = 0;
    int64_t k = 0;
    std::cin >> n >> k;
    assert(n >= k);

    std::vector<int64_t> weights(n);
    int64_t sum = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> weights[i];
        sum += weights[i];
        sum %= modulo::MODULO;
    }

    if (n == k)
    {
        std::cout << sum;
    }
    else
    {
        std::vector<int64_t> factorial(n);
        std::vector<int64_t> inverse_factorial(n);
        factorial[0]         = 1;
        inverse_factorial[0] = 1;
        for (int64_t i = 1; i < n; ++i)
        {
            factorial[i] = moduled_mult(factorial[i - 1],i, modulo::MODULO);
            inverse_factorial[i] = moduled_mult(inverse_factorial[i - 1],
                                                get_inverse(i, modulo::MODULO),
                                                modulo::MODULO);
        }

        std::cout << sum * get_stirling_sum(n, k, factorial, inverse_factorial) % modulo::MODULO;
    }

    return 0;
}
