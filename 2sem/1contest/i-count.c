#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const int STATES_QUANTITY = 4;

enum State
{
    OUT = -1,
    PARENTESIS_AND_STAR_COMM,
    CURLY_BRACKET_COMM,
    TWO_SLASH_COMM,
    SINGLE_QMARK_LITERAL
};

void CountComments(int *count_states_array, enum State state)
{
    assert(count_states_array != NULL);

    char first_next_symbol  = 0;
    char second_next_symbol = 0;

    while ((first_next_symbol = getchar()) != EOF)
    {
        if (((state == OUT)                       && ((first_next_symbol == '(') || (first_next_symbol == '/'))) ||
            ((state == PARENTESIS_AND_STAR_COMM)  &&  (first_next_symbol == '*')))
        {
            second_next_symbol = getchar();
        }
        else
        {
            second_next_symbol = 0;
        }
        
        switch (state)
        {
            case OUT:
                if ((first_next_symbol == '(') && (second_next_symbol == '*'))
                {
                    state = PARENTESIS_AND_STAR_COMM;
                }
                else if ((first_next_symbol == '/') && (second_next_symbol == '/'))
                {
                    state = TWO_SLASH_COMM;
                }
                else if (first_next_symbol == '{')
                {
                    state = CURLY_BRACKET_COMM;
                }
                else if (first_next_symbol == '\'')
                {
                    state = SINGLE_QMARK_LITERAL;
                }
                else if (second_next_symbol == '{')
                {
                    state = CURLY_BRACKET_COMM;
                }
                else if (second_next_symbol == '\'')
                {
                    state = SINGLE_QMARK_LITERAL;
                }
                break;
            
            case PARENTESIS_AND_STAR_COMM:
                if ((first_next_symbol == '*') && (second_next_symbol == ')'))
                {
                    ++count_states_array[(int) PARENTESIS_AND_STAR_COMM];
                    state = OUT;
                }
                break;

            case CURLY_BRACKET_COMM:
                if ((first_next_symbol == '}') || (second_next_symbol == '}'))
                {
                    ++count_states_array[(int) CURLY_BRACKET_COMM];
                    state = OUT;
                }
                break;

            case TWO_SLASH_COMM:
                if ((first_next_symbol == '\n') || (second_next_symbol == '\n'))
                {
                    ++count_states_array[(int) TWO_SLASH_COMM];
                    state = OUT;
                }
                break;
             
            case SINGLE_QMARK_LITERAL:
                if ((first_next_symbol == '\'') || (second_next_symbol == '\''))
                {
                    ++count_states_array[(int) SINGLE_QMARK_LITERAL];
                    state = OUT;
                }
                break;

            default: 
                state = OUT;
        } 
    }
}

int main()
{
    enum State state = OUT;
    int *count_states_array = (int *) calloc(STATES_QUANTITY, sizeof(int)); 

    CountComments(count_states_array, state);

    for (int i = 0; i < STATES_QUANTITY; ++i)
    {
        printf("%d ", count_states_array[i]);
    }

    free(count_states_array);

    return 0;
}   