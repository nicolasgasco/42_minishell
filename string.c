#include "minishell.h"

// Concatenate two strings and free first one
char    *ft_strcat(char *src, char *dest)
{
    int     i;
    int     y;
    char    *result;

    i = 0;
    y = 0;
    result = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(dest) + 1));
    if (!result)
        exit (1);
    while (src[i] != '\0')
    {
        result[y] = src[i];
        y++;
        i++;
    }
    i = 0;
    while (dest[i] != '\0')
    {
        result[y] = dest[i];
        y++;
        i++; 
    }
    result[y] = '\0';
    free(src);
    return (result);
}

// Remove character specified by index, NO FREE
char    *ft_remove_char_index(char *line, int index)
{
    int i;
    int y;
    char *result;

    result = malloc(sizeof(char) * (ft_strlen(line) - 1 + 1));
    i = 0;
    y = 0;
    while (line[i] != '\0')
    {
        if (i != index)
        {
            result[y] = line[i];
            y++;
        }
        i++;
    }
    result[y] = '\0';
    return (result);
}

// Actual token text is written into node ignoring quotes
char    *ft_create_quoted_token(char *input, int start, int len)
{
    char    *result;
    int     result_len;
    int     i;
    int     y;

    i = start;
    result_len = len;
    if (input[start + len - 1] == '\"' || input[start + len - 1] == '\'')
        result_len--;
    if (input[i] == '\"' || input[i] == '\'')
    {
        result_len--;
        i++;
    }
    y = 0;
    result = malloc(sizeof(char) * (result_len + 1));
    while (result_len != 0)
    {
        result[y] = input[i];
        i++;
        y++;
        result_len--;
    }
    result[y] = '\0';
    return (result);
}