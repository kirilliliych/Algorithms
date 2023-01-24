#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    scanf("%d", &N);

    for (int i = 0; i < (1 << N); ++i)
    {
        char *gray_number_str = (char *) calloc(N + 1, sizeof(char));
        gray_number_str[N] = '\0';

        int gray_code = (i >> 1) ^ i;
        int counter = N - 1;
        while (gray_code > 0)
        {
            gray_number_str[counter] = gray_code % 2 + '0';
            gray_code /= 2;

            --counter;
        }

        while (counter > -1)
        {
            gray_number_str[counter] += '0';

            --counter;
        }

        printf("%s", gray_number_str);
        printf("\n");
    }

    return 0;
}