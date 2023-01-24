#include <stdio.h>

void GetIndex(int *index, int cur_elem, int N, int K)
{
    if (cur_elem > N)
    {
        --(*index);
        return;
    }

    if (cur_elem == K)
    {
        printf("%d", *index);
    }

    ++(*index);
    GetIndex(index, cur_elem * 10, N, K);
    
    if (cur_elem % 10 == 9)
    {
        return;
    }

    ++(*index);
    GetIndex(index, cur_elem + 1, N, K);

    return;
}

int main()
{
    long long N = 0;
    long long K = 0;
    scanf("%lld %lld", &N, &K);

    int index = 1;
    GetIndex(&index, 1, N, K);
    return 0;
}