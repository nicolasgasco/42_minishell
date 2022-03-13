#include "minishell.h"

// Concatenate two strings and free first one
char    *ft_strcat(char *src, char *dest)
{
    int     i;
    int     y;
    char    *result;

    i = 0;
    y = 0;
    result = (char *)malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(dest) + 1));
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
