#include "minishell.h"

// Loof for a Here document structure in the string 
int ft_find_here_marker(char *str)
{
    int i;

    i = 1;
    if (ft_strlen(str) < 4)
        return (-1);
    while (str[i + 2] != '\0')
    {
        if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<'
        && str[i + 2] != '|' && str[i + 2] != '<' && str[i + 2] != '>')
        {
            return (1);
        }
        i++;
    }
    if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<')
        return (1);
    return (0);
}