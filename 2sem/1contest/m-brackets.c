#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_STRING_SIZE           = 102400;
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

int if_string_correct(struct stack *st);

struct stack *stack_new(size_t elem_size);

int stack_push(struct stack *st, const void *elem);

int stack_pop(struct stack *st, void *elem);

int stack_top(struct stack *st, void *elem);

int stack_empty(struct stack const *st);

struct stack *stack_delete(struct stack *st);

void stack_print(struct stack const *st, void(*pf)(void const *st));

int stack_resize_bigger(struct stack *st);

void stack_resize_smaller(struct stack *st);

int main()
{
    struct stack *stk = stack_new(sizeof(unsigned char));

    if (if_string_correct(stk))
    {
        printf("YES");    
    }
    else
    {
        printf("NO");
    }

    stack_delete(stk);
    
    return 0;
}

int if_string_correct(struct stack *st)
{
    assert(st != NULL);

    unsigned char cur_sym = 0;
    unsigned char popped_element = '\0';

    while ((cur_sym = getchar()) != '\n')
    {
        switch (cur_sym)
        {
            case '{':
            case '[':
            case '(':
            case '<':
                stack_push(st, &cur_sym);
                break;

            case '}':
            {
                int pop_result = stack_pop(st, &popped_element);
                if ((popped_element != '{') || (pop_result == 1))
                {
                    return 0;
                }
                break;
            }

            case ']':
            {
                int pop_result = stack_pop(st, &popped_element);
                if ((popped_element != '[') || (pop_result == 1))
                {
                    return 0;
                }
                break;
            }

            case ')':
            {
                int pop_result = stack_pop(st, &popped_element);
                if ((popped_element != '(') || (pop_result == 1))
                {
                    return 0;
                }
                break;
            }
            
            case '>':
            {
                int pop_result = stack_pop(st, &popped_element);
                if ((popped_element != '<') || (pop_result == 1))
                {
                    return 0;
                }
            }
        }
    }

    return stack_empty(st);
}

struct stack *stack_new(size_t elem_size)
{
    assert(elem_size > 0);

    struct stack *st = (struct stack *) calloc(1, sizeof(struct stack));

    st->capacity = STACK_MIN_CAPACITY;
    st->size = 0;
    st->elem_size = elem_size;
    st->data = (void *) calloc(STACK_MIN_CAPACITY, elem_size);

    return st;
}

int stack_push(struct stack *st, const void *elem)
{
    if ((st == NULL) || (elem == NULL))
    {
        return 1;
    }

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
    if ((st == NULL) || (elem == NULL) || (st->size == 0))
    {
        return 1;
    }

    //stack_resize_smaller(st);

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

    st->capacity  = 0;
    st->elem_size = 0;
    st->size = 0;

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

int stack_resize_bigger(struct stack *st)
{
    assert(st != NULL);

    void *new_memory = realloc(st->data, st->capacity * RESIZE_BIGGER_MULTIPLIER * st->elem_size);
    if (new_memory == NULL)
    {
        return 1;
    } 

    st->data = new_memory;
    st->capacity *= RESIZE_BIGGER_MULTIPLIER;

    return 0;
}

void stack_resize_smaller(struct stack *st)
{
    assert(st != NULL);

    if ((st->size * RESIZE_SMALLER_DIVISOR <= st->capacity) && (st->capacity > STACK_MIN_CAPACITY))
    {
        st->data = (int *) realloc(st->data, st->capacity / RESIZE_SMALLER_DIVISOR * st->elem_size);
        st->capacity /= RESIZE_SMALLER_DIVISOR;
    }
}