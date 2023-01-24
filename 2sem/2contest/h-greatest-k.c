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

void heapify(struct binary_heap *bh, size_t index, size_t size)
{
    assert(bh != NULL);

    long long cur_index_value = bh->elements[index];
    size_t cur_index = index;

    for (;;)
    {
        size_t left  = index + index;
        size_t right = left + 1;

        if (bh->type == 0)
        {
            if ((left  <= size) && (bh->elements[left]  > cur_index_value))
            {
                cur_index = left;
            }    

            if ((right <= size) && (bh->elements[right] > bh->elements[cur_index]))
            {
                cur_index = right;
            }

            if (cur_index == index)
            {
                break;
            }
        }
        else
        {
            if ((left  <= size) && (bh->elements[left]  < cur_index_value))
            {
                cur_index = left;
            }    

            if ((right <= size) && (bh->elements[right] < bh->elements[cur_index]))
            {
                cur_index = right;
            }

            if (cur_index == index)
            {
                break;
            }
        }
        
        bh->elements[index] = bh->elements[cur_index];
        bh->elements[cur_index] = cur_index_value;
        index = cur_index;
    }
}

elem_t heap_delete_top(struct binary_heap *bh)
{
    assert(bh != NULL);
    assert(bh->cur_size > 0);

    elem_t deleted_element = bh->elements[bh->cur_size];

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
        printf("%lld\n", bh->elements[i]);
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


void heap_sort(struct binary_heap *bh, size_t size)
{
    assert(bh != NULL);

    for (size_t i = size / 2; i > 0; --i)
    {
        heapify(bh, i, size);
    }
    while (size > 1)
    {
        --size;
        heap_swap(bh, 1, size + 1);
        heapify(bh, 1, size);
    }
}

int main()
{
    long long N = 0;
    long long K = 0;
    scanf("%lld %lld", &N, &K);

    struct binary_heap *sequence = new_heap(K, 0);

    long long new_number = 0;
    for (long long number_index = 0; number_index < N; ++number_index)
    {
        scanf("%lld", &new_number);

        if (sequence->cur_size < sequence->max_size)
        {
            heap_insert(sequence, new_number);
        }
        else if (heap_top(sequence) < new_number)
        {
            heap_delete_top(sequence);
            heap_insert(sequence, new_number);
        }
    }
    
    sequence->type = 1;
    heap_sort(sequence, sequence->cur_size);
    heap_print(sequence);

    heap_destroy(sequence);

    return 0;
}