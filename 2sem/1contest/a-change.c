#include <stdio.h>
#include <math.h>

const int CHEAP_COIN_VALUE = 5;

int main()
{
    int N = 0;
    scanf("%d", &N);
    int cheap_coins_number = 0;
    int cur_cheap_coins_number = 0;

    for (int i = 0; i < N; ++i)
    {
        int new_coin_value = 0;
        scanf("%d", &new_coin_value);
        
        if (new_coin_value == CHEAP_COIN_VALUE)
        {
            ++cur_cheap_coins_number;
        } 
        else
        {
            if (cur_cheap_coins_number * CHEAP_COIN_VALUE >= new_coin_value - CHEAP_COIN_VALUE)
            {
                cur_cheap_coins_number -= new_coin_value / CHEAP_COIN_VALUE - 1;
            }
            else
            {
                cheap_coins_number += new_coin_value / CHEAP_COIN_VALUE - cur_cheap_coins_number - 1;
                cur_cheap_coins_number = 0;
            }
        }

    }

    printf("%d", cheap_coins_number);

    return 0;
}