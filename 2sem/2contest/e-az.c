#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const int LETTERS_QUANTITY = 26;

struct letter_signature
{
    int number;
    char letter;
};

int Comparator(const void *letter_signature1, const void *letter_signature2)
{
    assert(letter_signature1 != NULL);
    assert(letter_signature2 != NULL);

    if (((struct letter_signature *) letter_signature1)->number - ((struct letter_signature *) letter_signature2)->number == 0)
    {
        return ((struct letter_signature *) letter_signature2)->letter - ((struct letter_signature *) letter_signature1)->letter;
    }

    return ((struct letter_signature *) letter_signature1)->number - ((struct letter_signature *) letter_signature2)->number;
}

int main()
{
   struct letter_signature *letters = (struct letter_signature *) calloc(LETTERS_QUANTITY, sizeof(struct letter_signature));
    for (int i = 0; i < LETTERS_QUANTITY; ++i)
    {
        letters[i].letter = 'A' + i;
    }

    int new_char = 0;
    while ((new_char = getchar()) != '\n')
    {
        ++letters[new_char - 'A'].number;
    }

    qsort(letters, LETTERS_QUANTITY, sizeof(struct letter_signature), Comparator);

    for (int i = LETTERS_QUANTITY - 1; i > -1; --i)
    {
        if (letters[i].number == 0)
        {
            break;
        }
        
        printf("%c %d\n", letters[i].letter, letters[i].number);
    }

    free(letters);

    return 0;
}