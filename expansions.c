#include "minishell.h"

// Function identifies first valid quoting character and proceed to expand quotes accordingly
char *ft_expand_line(char *line)
{
    int i;
    char    *result;

    i = ft_first_valid_quote(line);
    if (line[i] == '\'')
    {
        printf("Expanding simple quotes...\n");
        result = ft_expand_simple_quotes(line);
    }
    else if (line[i] == '"')
    {
        printf("First quote is %c\n", line[i]);
        result = malloc(4);
        result[0] = 'c';
        result[1] = 'i';
        result[2] = 'a';
        result[3] = '\0';
    }
    free(line);
    return (result);
}