#include <stdio.h>
#include <stdlib.h>

char GetSymbolOnPos(int num_in_sequence, int num_in_row)
{
    if (num_in_row == 1)
    {
        return 'a' + num_in_sequence - 1; 
    }

    if (num_in_row <= (1 << (num_in_sequence - 1)))
    {
        return GetSymbolOnPos(num_in_sequence - 1, num_in_row - 1);
    }
    else
    {
        return GetSymbolOnPos(num_in_sequence - 1, num_in_row - (1 << (num_in_sequence - 1)));
    }
}

int main()
{
    int N = 0;
    int K = 0;
    int L = 0;
    scanf("%d %d %d", &N, &K, &L);
    
    for (int i = K; i < L + 1; ++i)
    {
        printf("%c", GetSymbolOnPos(N, i));
    }
    return 0;
}