#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int compare(const void *value_1, const void *value_2)
{
    assert(value_1 != NULL);
    assert(value_2 != NULL);

    return *((long long *) value_1) - *((long long *) value_2);
}

int main()
{
    long long *first_set  = (long long *) calloc(100001, sizeof(long long));
    long long *second_set = (long long *) calloc(100001, sizeof(long long));

    int first_set_size  = 0;
    long long new_num = 1;
    int counter = 0;

    while (new_num != 0)
    {
        scanf("%lld", &new_num);

        first_set[counter] = new_num;
        ++counter;
    }
    first_set_size = counter - 1;

    counter = 0;
    new_num = 1;
    while (new_num != 0)
    {
        scanf("%lld", &new_num);

        second_set[counter] = new_num;
        ++counter;
    }
    --counter;

    qsort(first_set,  first_set_size, sizeof(long long), compare);
    qsort(second_set, counter, sizeof(long long), compare);

    long long *first_ptr  = first_set;
    long long *second_ptr = second_set;
    while ((*first_ptr != 0) && (*second_ptr != 0))
    {
        if (*first_ptr < *second_ptr)
        {
            printf("%lld ", *first_ptr);
            ++first_ptr;
        }
        else if (*first_ptr > *second_ptr)
        {
            printf("%lld ", *second_ptr);
            ++second_ptr;
        }
        else 
        {
            ++first_ptr;
            ++second_ptr;
        }
    }

    while (*first_ptr != 0)
    {
        printf("%lld ", *first_ptr);
        ++first_ptr;
    }

    while (*second_ptr != 0)
    {
        printf("%lld ", *second_ptr);
        ++second_ptr;
    }

    return 0;
}