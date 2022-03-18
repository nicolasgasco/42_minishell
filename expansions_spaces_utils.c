#include "minishell.h"

int ft_calc_spaces_token_len(char *str)
{
    int i;

    i = 0;
    while (!ft_isspace(str[i]))
        i++;
    return (i);
}

int ft_has_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (ft_isspace(str[i]))
            return (1);
        i++;
    }
    return (0);
}

int ft_isspace(char c)
{
    // if (c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f' || c == ' ')
    if (c == ' ')
        return (1);
    return (0);
}
