#include "minishell.h"

// All functions in this file will be deleted

void    ft_print_array(char **str_array)
{
    int i;

    i = 0;
    printf("Tokens: ");
    while (*(str_array + i))
    {
        printf("|%s| ", str_array[i]);
        i++;
    }
    printf("\n");
}
