#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int STACK_MIN_CAPACITY        = 4;
const int RESIZE_BIGGER_MULTIPLIER  = 2;
const int RESIZE_SMALLER_DIVISOR    = 4;
    
struct stack
{
    int capacity;
    int size;
    size_t elem_size;
    void *data;
};

struct column_characteristics
{
    long long height;
    long long position;

};

struct stack *stack_new(size_t elem_size);

int stack_push(struct stack *st, const void *elem);

int stack_pop(struct stack *st, void *elem);

int stack_top(struct stack *st, void *elem);

int stack_empty(struct stack const *st);

struct stack *stack_delete(struct stack *st);

void stack_print(struct stack const *st, void(*pf)(void const *st));

static int stack_resize_bigger(struct stack *st);

static void stack_resize_smaller(struct stack *st);

static long long count_max_area(struct column_characteristics *columns, int columns_quantity);

static long long count_positions(struct column_characteristics *columns, struct column_characteristics *new_column, 
                            struct stack *stk, long long *left_borders, long long column_index, int destination_flag);

int main()
{
    int N = 0;
    scanf("%d", &N);

    struct column_characteristics *columns = (struct column_characteristics *) calloc(N, sizeof(struct column_characteristics));
    for (long long i = 0; i < N; ++i)
    {
        scanf("%lld", &(columns[i].height));
        columns[i].position = i;
    }
    
    printf("%lld", count_max_area(columns, N));

    free(columns);
    return 0;
}


struct stack *stack_new(size_t elem_size)
{
    assert(elem_size > 0);

    struct stack *st = (struct stack *) calloc(1, sizeof(struct stack));

    st->capacity = 0;
    st->size = 0;
    st->elem_size = elem_size;
    st->data = NULL;

    return st;
}

int stack_push(struct stack *st, const void *elem)
{
    assert(st != NULL);
    assert(elem != NULL);

    if (st->size == st->capacity)
    {
        if (stack_resize_bigger(st))
        {
            return 1;
        }   
    }

    memcpy(st->data + st->elem_size * st->size, elem, st->elem_size);
    ++st->size;

    return 0;
}

int stack_pop(struct stack *st, void *elem)
{
    assert(st != NULL);

    if (st->size == 0)
    {
        return 1;
    }

    stack_resize_smaller(st);

    --st->size;
    memcpy(elem, st->data + st->elem_size * st->size, st->elem_size);

    return 0;
}

int stack_top(struct stack *st, void *elem)
{
    assert(st != NULL);

    if (st->size == 0)
    {
        return 1;
    }

    memcpy(elem, st->data + st->elem_size * (st->size - 1), st->elem_size);

    return 0;
}

int stack_empty(struct stack const *st)
{
    assert(st != NULL);

    return st->size == 0;
}

struct stack *stack_delete(struct stack *st)
{
    assert(st != NULL);

    free(st->data);
    free(st);
    return NULL;
}

void stack_print(struct stack const *st, void(*pf)(void const *st))
{
    assert(st != NULL);
    assert(pf != NULL);

    printf("[");

    for (int elem_index = 0; elem_index < st->size; ++elem_index)
    {
        pf(st->data + elem_index * st->elem_size);

        if (elem_index < st->size - 1)
        {
            printf(", ");
        }
    }

    printf("]\n");
}

static int stack_resize_bigger(struct stack *st)
{
    assert(st != NULL);

    if (st->capacity == 0)
    {
        void *new_memory = calloc(STACK_MIN_CAPACITY, st->elem_size);
        if (new_memory == NULL)
        {
            return 1;
        }

        st->data = new_memory;
        st->capacity = STACK_MIN_CAPACITY;
    }

    void *new_memory = realloc(st->data, st->capacity * RESIZE_BIGGER_MULTIPLIER * st->elem_size);
    if (new_memory == NULL)
    {
        return 1;
    } 

    st->data = new_memory;
    st->capacity = st->capacity * RESIZE_BIGGER_MULTIPLIER;

    return 0;
}

static void stack_resize_smaller(struct stack *st)
{
    assert(st != NULL);

    if ((st->size * RESIZE_SMALLER_DIVISOR <= st->capacity) && (st->capacity > STACK_MIN_CAPACITY))
    {
        st->data = (int *) realloc(st->data, st->capacity / RESIZE_SMALLER_DIVISOR * st->elem_size);
        st->capacity /= RESIZE_SMALLER_DIVISOR;
    }
}

static long long count_max_area(struct column_characteristics *columns, int columns_quantity)                    // основная идея: находясь в итерации на i-м столбике, объявляем его минимальным во всем искомом прямоугольнике; за один проход слева направо находим для каждого столбика самый левый такой, что все между ними не меньше i-го столбика; найденный столбик и будет левой границей потенциального прямоугольника; делая аналогичный проход справа налево, получаем правые границы, затем для каждого столбика считаем максимальную площадь прямоугольника, образованного такими условиями
{
    assert(columns != NULL);

    struct column_characteristics *new_column = (struct column_characteristics *) calloc(1, sizeof(struct column_characteristics)); 
    long long *left_borders = (long long *) calloc(columns_quantity, sizeof(long long)); 

    struct stack *stk = stack_new(sizeof(struct column_characteristics));

    for (long long column_index = 0; column_index < columns_quantity; ++column_index)
    {
        count_positions(columns, new_column, stk, left_borders, column_index, 0);                                // 0 - флаг направления; показывает, что мы отмечаем крайние позиции слева, идя по массиву высот слева, и записываем их в каждый четный элемент массива границ (left_borders)
    }
    stk = stack_delete(stk);

    new_column->height   = 0;
    new_column->position = columns_quantity - 1;

    long long max_area = 0;
    stk = stack_new(sizeof(struct column_characteristics));
    for (long long column_index = columns_quantity - 1; column_index > -1; --column_index)
    {
        long long cur_area = count_positions(columns, new_column, stk, left_borders, column_index, 1);           // 1 - флаг направления; показывает, что мы отмечаем крайние позиции справа, идя по массиву высот справа, и считаем размер прямоугольника
        if (cur_area > max_area)
        {
            max_area = cur_area;
        }
    }

    stk = stack_delete(stk);
    free(new_column);
    free(left_borders);

    return max_area;
}

static long long count_positions(struct column_characteristics *columns, struct column_characteristics *new_column, 
                                 struct stack *stk, long long *left_borders, long long column_index, int destination_flag)
{
    if ((stack_top(stk, new_column) == 1) || (columns[column_index].height > new_column->height))
    {
        ++new_column->height;
        new_column->position = column_index;

        while (new_column->height <= columns[column_index].height)
        {
            stack_push(stk, new_column);
             ++new_column->height;
        }
        --new_column->height;

        if (destination_flag == 0)
        {
            left_borders[column_index] = column_index; 
        }
        else
        {
            return (column_index - left_borders[column_index] + 1) * columns[column_index].height;
        }
    }
    else
    {
        int stack_top_result = stack_top(stk, new_column);
        while ((stack_top_result == 0) && (columns[column_index].height < new_column->height)) 
        {
            stack_pop(stk, new_column);
            stack_top_result = stack_top(stk, new_column);
        }

        if (destination_flag == 0)
        {
            left_borders[column_index] = (stack_top_result == 1) ? column_index : new_column->position;
        }
        else
        {
            if (stack_empty(stk))
            {
                new_column->height = 0;
                new_column->position = 0;
            }
            return (new_column->position - left_borders[column_index] + 1) * columns[column_index].height;      // works if zero
        }
    }

    return 0;
}

// сложность:  требуется один полный проход по массиву влево, один вправо  - всего 2 прохода, 2 * N = O(N)