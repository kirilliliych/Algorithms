#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_STR_SIZE     = 100;
const size_t MAX_STR_QUANTITY = 100;

int Strcmp(const void *str1, const void *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    const char *ptr1 = *((const char **) str1);
    const char *ptr2 = *((const char **) str2);

    char *united_1 = (char *) calloc(210, sizeof(char));
    strcat(united_1, ptr1);
    strcat(united_1, ptr2);

    char *united_2 = (char *) calloc(210, sizeof(char));
    strcat(united_2, ptr2);
    strcat(united_2, ptr1);

    int result = -strcmp(united_1, united_2);

    free(united_1);
    free(united_2); 

    return result;
}

int main()
{
    size_t str_place = 0;
    char **str_array = (char **) calloc(MAX_STR_QUANTITY, sizeof(char *));
    for (int i = 0; i < MAX_STR_QUANTITY; ++i)
    {
        str_array[i] = (char *) calloc(MAX_STR_SIZE + 2,  sizeof(char));
    }
    
    while (fgets(str_array[str_place], MAX_STR_SIZE + 2, stdin) != NULL)
    {
        (str_array[str_place])[strlen(str_array[str_place]) - 1] = '\0';
    
        ++str_place;
    }

    qsort(str_array, str_place, sizeof(char *), Strcmp);

    for (size_t i = 0; i < str_place; ++i)
    {
        printf("%s", str_array[i]);
    }

    for (int i = 0; i < MAX_STR_QUANTITY; ++i)
    {
        free(str_array[i]);
    }
    free(str_array);

    return 0;
}