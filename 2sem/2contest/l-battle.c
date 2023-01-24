#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long Ceil(long long dividend, long long divisor)
{
    assert(divisor != 0);

    return (dividend - 1) / divisor + 1;
}

int IfStrikesEnough(long long *hitpoints, long long enemies_number, long long tunnel_damage,
                    long long aoe_damage, long long strikes)
{
    assert(hitpoints != NULL);

    long long strikes_needed_more = 0;
    for (long long i = 0; i < enemies_number; ++i)
    {
        if (hitpoints[i] > aoe_damage * strikes)
        {
            strikes_needed_more += Ceil(hitpoints[i] - aoe_damage * strikes, tunnel_damage - aoe_damage);

            if (strikes_needed_more > strikes)
            {
                return 0;
            }
        }
    }

    return 1;
}

void BinarySearch(long long *hitpoints,    long long *strikes,   long long enemies_number, 
                  long long tunnel_damage, long long aoe_damage, long long low_border,
                  long long high_border)
{
    assert(hitpoints != NULL);
    assert(strikes   != NULL);

    if (low_border > high_border)
    {
        return;
    }
    
    long long middle = (low_border + high_border) / 2;

    if (IfStrikesEnough(hitpoints, enemies_number, tunnel_damage, aoe_damage, middle))
    {
        *strikes = middle;

        BinarySearch(hitpoints, strikes, enemies_number, tunnel_damage, aoe_damage,
                     low_border, middle - 1);
    }
    else
    {
        BinarySearch(hitpoints, strikes, enemies_number, tunnel_damage, aoe_damage,
                     middle + 1, high_border);
    }
}

int main()
{   
    long long n = 0;
    long long p = 0;
    long long q = 0;
    scanf("%lld %lld %lld", &n, &p, &q);

    long long boss_hitpoints = 0;
    long long *hitpoints_values = (long long *) calloc(n, sizeof(long long)); 
    for (long long i = 0; i < n; ++i)
    {
        scanf("%lld", &hitpoints_values[i]);
        if (boss_hitpoints < hitpoints_values[i])
        {
            boss_hitpoints = hitpoints_values[i];
        }
    }

    if (p == q)
    {
        printf("%lld", Ceil(boss_hitpoints, q));
    }
    else
    {
        long long strikes = 0;
        BinarySearch(hitpoints_values, &strikes, n, p, q, 1, Ceil(boss_hitpoints, q));
        printf("%lld", strikes);
    }

    free(hitpoints_values);

    return 0;
}