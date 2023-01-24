#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct time
{
    int time;
    int inside_or_outside;
};

const int TIME_STR_LENGTH = 9;
const int HOUR_MULTIPLIER = 60 * 60;


int Comparator(const void *first_dude, const void *second_dude)
{
    assert(first_dude  != NULL);
    assert(second_dude != NULL);

    if (((const struct time *) first_dude)->time - ((const struct time *) second_dude)->time == 0)
    {
        return ((const struct time *) first_dude)->inside_or_outside - ((const struct time *) second_dude)->inside_or_outside;
    }

    return ((const struct time *) first_dude)->time - ((const struct time *) second_dude)->time;
}

int main()
{
    int N = 0;
    scanf("%d", &N);

    struct time *time_array = (struct time *) calloc(N * 2, sizeof(struct time));

    for (int i = 0; i < N * 2; ++i)
    {
        char time_input[TIME_STR_LENGTH];
        
        scanf("%8s", time_input);

        int time_value = 0;
        int multiplier = HOUR_MULTIPLIER;

        for (int str_index = 0; str_index < TIME_STR_LENGTH - 1; ++str_index)
        {
            if (str_index % 3 == 2)
            {
                continue;
            }
            
            if (str_index % 3 == 0)
            {
                multiplier *= 10;
            }

            time_value += (time_input[str_index] - '0') * multiplier;

            if (str_index % 3 == 0)
            {
                multiplier /= 10;
            }

            if (str_index % 3 == 1)
            {
                multiplier /= 60;
            }
            
        }

        time_array[i].time = time_value;
        if (i % 2 == 0)
        {
            time_array[i].inside_or_outside  = 0;
        }
        else time_array[i].inside_or_outside = 1;
    }

    qsort(time_array, N * 2, sizeof(struct time), Comparator);

    int max_dudes_quantity = 0;
    int cur_dudes_quantity = 0;
    
    for (int i = 0; i < N * 2; ++i)
    {
        if (time_array[i].inside_or_outside % 2 == 0)
        {
            ++cur_dudes_quantity;
        }
        else
        {
            --cur_dudes_quantity;
        }

        if (max_dudes_quantity < cur_dudes_quantity)
        {
            max_dudes_quantity = cur_dudes_quantity;
        }
    }

    printf("%d", max_dudes_quantity);

    free(time_array);

    return 0;
}