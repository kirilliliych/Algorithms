#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define aboba printf("aboba %d\n", __LINE__);

struct point
{
    long long x;
    long long y;
    long long z;
};

int Comparator(const void *val1, const void *val2);

int main()
{       
    long long N = 0;
    scanf("%lld", &N);

    struct point *points_array = (struct point *) calloc(N, sizeof(struct point));
    for (long long i = 0; i < N; ++i)
    {
        scanf("%lld", &points_array[i].x);
        scanf("%lld", &points_array[i].y);
        scanf("%lld", &points_array[i].z);
    }

    qsort(points_array, N, sizeof(struct point), Comparator);
    struct point *small_ptr = points_array;
    struct point *big_ptr   = points_array + N - 1;
    struct point probable   = {
                               small_ptr->x + big_ptr->x,
                               small_ptr->y + big_ptr->y,
                               small_ptr->z + big_ptr->z
                              };

    ++small_ptr;
    --big_ptr;

    while (small_ptr <= big_ptr)
    {
        if (small_ptr->x + big_ptr->x != probable.x)
        {
            printf("No");
            break;
        }
        if (small_ptr->y + big_ptr->y != probable.y)
        {
            printf("No");
            break;
        }
        if (small_ptr->y + big_ptr->y != probable.y)
        {
            printf("No");
            break;
        }

        ++small_ptr;
        --big_ptr;
    }

    if (small_ptr > big_ptr)
    {
        printf("Yes");
    }

    free(points_array);

    return 0;
}

int Comparator(const void *val1, const void *val2)
{
    assert(val1 != NULL);
    assert(val2 != NULL);

    const struct point *point1 = (const struct point *) val1;
    const struct point *point2 = (const struct point *) val2;
    
    if (point1->x < point2->x)
    {
        return -1;
    }
    else if (point1->x > point2->x)
    {
        return 1;
    }

    if (point1->y < point2->y)
    {
        return -1;
    }
    else if (point1->y > point2->y)
    {
        return 1;
    }

    if (point1->z < point2->z)
    {
        return -1;
    }
    else if (point1->z > point2->z)
    {
        return 1;
    }

    return 0;
}