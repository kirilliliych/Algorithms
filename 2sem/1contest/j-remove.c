#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum State
{
    OUT,
    SLASH_AND_STAR_COMM,
    TWO_SLASH_COMM,
    STRING
};

void DeleteComments(enum State state)
{
    char first_next_symbol  = 0;
    char second_next_symbol = 0;

    while ((first_next_symbol = getchar()) != EOF)
    {
        int second_read = 0;
        if ((state == OUT) && (first_next_symbol == '/'))
        {
            second_read = 1;
            second_next_symbol = getchar();
        }
        
        switch (state)
        {
            case OUT:
                if ((first_next_symbol == '/') && (second_next_symbol == '*'))
                {
                    state = SLASH_AND_STAR_COMM;
                }
                else if ((first_next_symbol == '/') && (second_next_symbol == '/'))
                {
                    state = TWO_SLASH_COMM;
                }
                else if ((first_next_symbol == '\'') || (first_next_symbol == '"'))
                {
                    state = STRING;
                    printf("%c", first_next_symbol);
                }
                else
                {
                    printf("%c", first_next_symbol);
                    if (second_read)
                    {
                        printf("%c", second_next_symbol);
                    }
                }
                break;
            
            case SLASH_AND_STAR_COMM:
                if (first_next_symbol == '*')
                {
                    second_next_symbol = getchar();
                    if (second_next_symbol == '/')
                    {
                        state = OUT;
                        printf(" ");
                    }
                }
                break;

            case TWO_SLASH_COMM:
                if (first_next_symbol == '\n')
                {
                    printf("%c", first_next_symbol);
                    state = OUT;
                }
                break;
             
            case STRING:
                if ((first_next_symbol == '\'') || (first_next_symbol == '"'))
                {
                    state = OUT;
                }
                printf("%c", first_next_symbol);
                break;

            default: 
                state = OUT;
        } 
    }
}

int main()
{
    enum State state = OUT; 

    DeleteComments(state);

    return 0;
}