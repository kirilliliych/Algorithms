#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long elem_t;

struct binary_heap
{
    size_t max_size;
    size_t cur_size;
    size_t type;
    elem_t *elements;
};

void heap_print(struct binary_heap *bh);

struct binary_heap *new_heap(size_t max_size, size_t type)
{
    struct binary_heap *bh = (struct binary_heap *) calloc(1, sizeof(struct binary_heap)); 

    bh->elements = (elem_t *) calloc(max_size + 1, sizeof(elem_t));
    bh->max_size = max_size;
    bh->cur_size = 0;
    bh->type = type;    

    return bh;
}

void heap_destroy(struct binary_heap *bh)
{
    assert(bh != NULL);

    free(bh->elements);
    free(bh);
}

void heap_swap(struct binary_heap *bh, size_t index1, size_t index2)
{
    assert(bh != NULL);

    elem_t temp = bh->elements[index1];
    bh->elements[index1] = bh->elements[index2];
    bh->elements[index2] = temp;
}

elem_t heap_top(struct binary_heap *bh)
{
    assert(bh != NULL);
    assert(bh->cur_size > 0);

    return bh->elements[1];
}

void heap_siftUp(struct binary_heap *bh, size_t index)
{
    assert(bh != NULL);

    if (bh->type == 0)
    {
        for (size_t i = index; 
             i > 1 && bh->elements[i] < bh->elements[i / 2]; 
             i /= 2)
        {
            heap_swap(bh, i, i / 2);
        }
    }
    else
    {
        for (size_t i = index;
             i > 1 && bh->elements[i] > bh->elements[i / 2];
             i /= 2)
        {
            heap_swap(bh, i, i / 2);
        }
    }
}

void heap_insert(struct binary_heap *bh, elem_t elem)
{
    assert(bh != NULL);
    assert(bh->cur_size < bh->max_size);

    ++bh->cur_size;
    bh->elements[bh->cur_size] = elem;
    heap_siftUp(bh, bh->cur_size);
}

void heap_siftDown(struct binary_heap *bh, size_t index)
{
    assert(bh != NULL);

    for (;;)
    {
        size_t left  = index + index;
        size_t right = left  + 1;

        size_t smallest = index;

        if (bh->type == 0)
        {
            if ((left  <= bh->cur_size) && (bh->elements[left]  < bh->elements[smallest]))
            {
                smallest = left;
            }

            if ((right <= bh->cur_size) && (bh->elements[right] < bh->elements[smallest]))
            {
                smallest = right;
            }

            if (smallest == index)
            {
                break;
            }
        } 
        else
        {
            if ((left  <= bh->cur_size) && (bh->elements[left]  > bh->elements[smallest]))
            {
                smallest = left;
            }

            if ((right <= bh->cur_size) && (bh->elements[right] > bh->elements[smallest]))
            {
                smallest = right;
            }

            if (smallest == index)
            {
                break;
            }
        }
        
        heap_swap(bh, index, smallest);
        index = smallest;
    }
}

elem_t heap_delete_top(struct binary_heap *bh)
{
    assert(bh != NULL);
    assert(bh->cur_size > 0);

    elem_t deleted_element = heap_top(bh);

    --bh->cur_size;

    if (bh->cur_size > 0)
    {
        heap_swap(bh, 1, bh->cur_size + 1);
        heap_siftDown(bh, 1);
    }

    return deleted_element;
}

size_t heap_size(struct binary_heap *bh)
{
    assert(bh != NULL);

    return bh->cur_size;
}

void heap_print(struct binary_heap *bh)
{
    assert(bh != NULL);

    for (size_t i = 1; i < bh->cur_size + 1; ++i)
    {
        printf("%lld ", bh->elements[i]);
    }
    printf("\n");
}

void heap_cat(struct binary_heap *dest, struct binary_heap *source)
{
    assert(dest   != NULL);
    assert(source != NULL);

    for (int i = 1; i < source->cur_size + 1; ++i)
    {
        heap_insert(dest, source->elements[i]);
    }

    source->cur_size = 0;
}

void print_median(struct binary_heap *min_heap, struct binary_heap *max_heap)
{
    assert(min_heap != NULL);
    assert(max_heap != NULL);

    if ((min_heap->cur_size + max_heap->cur_size) % 2 == 0)
    {
        printf("%lld\n", heap_top(min_heap));
    }
    else
    {
        printf("%lld\n", heap_top(max_heap));
    }
}

void insert_and_balance(struct binary_heap *min_heap, struct binary_heap *max_heap,
                        elem_t new_value)
{
    assert(min_heap != NULL);
    assert(max_heap != NULL);

    if ((max_heap->cur_size == 0) || (new_value > heap_top(max_heap)))
    {
        heap_insert(max_heap, new_value);
    }
    else
    {
        heap_insert(min_heap, new_value);
    }

    while (max_heap->cur_size > min_heap->cur_size + 1)                                 // + 1 to ensure that max_heap->cur_size always >= min_heap->cur_size
    {
        heap_insert(min_heap, heap_delete_top(max_heap));
    }

    while (min_heap->cur_size > max_heap->cur_size)
    {
        heap_insert(max_heap, heap_delete_top(min_heap));
    }
}

int main()
{
    long long N = 0;
    scanf("%lld", &N);
    
    struct binary_heap *min_heap = new_heap(N, 1);
    struct binary_heap *max_heap = new_heap(N, 0);

    for (long long i = 0; i < N; ++i)
    {
        int command_number = 0;
        scanf("%d", &command_number);
        if (command_number == 0)
        {
            elem_t new_value = 0;
            scanf("%lld", &new_value);

            insert_and_balance(min_heap, max_heap, new_value);
        }
        else
        {
            print_median(min_heap, max_heap);
        }
    }

    heap_destroy(min_heap);
    heap_destroy(max_heap);

    return 0;
}