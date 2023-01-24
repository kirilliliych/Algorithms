#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    int M = 0;
    int mod = 0;
    scanf("%d %d %d", &N, &M, &mod);
    
    int *coeffs = (int *) calloc(N + 1, sizeof(int));
    for (int i = 0; i < N + 1; ++i)
    {
        scanf("%d", &coeffs[i]);
    }

    int *results = (int *) calloc(M, sizeof(int));
    for (int i = 0; i < M; ++i)
    {
        int arg = 0;
        scanf("%d", &arg);
        
        //long long result = (coeffs[0] * arg + coeffs[1]) % mod;
        long long result = 0;
        
        for (int j = 0; j < N + 1; ++j)
        {
            result *= arg;
            result += coeffs[j];
            result %= mod;

        }

        results[i] = result;
    }

    for (int i = 0; i < M; ++i)
    {
        printf("%d\n", results[i]);
    }

    free(results);
    free(coeffs);
    
    return 0;
}