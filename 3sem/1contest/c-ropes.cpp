#include <cassert>
#include <climits>
#include <cmath>
#include <iostream>


#define aboba std::cout << "aboba " << __LINE__ << std::endl;


int Comparator(const void *val1, const void *val2)
{
    return *((long long *) val1) > *((long long *) val2) ? 1 : *((long long *) val1) == *((long long *) val2) ? 0 : -1; 
}

long long Min(long long val1, long long val2)
{
    return val1 > val2 ? val2 : val1;
}

long long CountRopesLengthSum(long long *axis, long long N)
{
    assert(axis != nullptr);

    long long *min_lengths = new long long[N - 1];
    min_lengths[0] = axis[1] - axis[0];                                                         // initializing base
    min_lengths[1] = axis[2] - axis[0];
    for (long long i = 2; i < N - 1; ++i)
    {
        min_lengths[i] = Min(min_lengths[i - 2], min_lengths[i - 1]) + axis[i + 1] - axis[i];
        // std::cout << "min_lengths[" << i << "]: " << min_lengths[i] << std::endl;

    }
    long long result = min_lengths[N - 2];

    delete [] min_lengths;

    return result;
}


int main()
{
    size_t N = 0;
    std::cin >> N;

    long long *axis = new long long[N];
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> axis[i];
    }

    qsort(axis, N, sizeof(axis[0]), Comparator);
    std::cout << CountRopesLengthSum(axis, N) << std::endl;

    delete [] axis;

    return 0;
}