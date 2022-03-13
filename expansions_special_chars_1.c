#include "minishell.h"

// Check if a character is invalid for Here document structure
int ft_found_invalid_character(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"' || c == '!')
        return (1);
    return (0);
}

int ft_found_special_character(char c)
{
    if (c == '|' || c == '>' || c == '<')
        return (1);
    return (0);
}

int ft_found_pipe(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\0')
        return (0);
    if (str[i] == '|' && str[i + 1] != '|')
        return (1);
    while (str[i + 1] != '\0')
    {
        if (str[i] == '|' && str[i + 1] != '|')
            return (1);
        i++;
    }
    if (str[i] == '|')
        return (1);
    return (0);
}

int ft_found_redirection(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\0')
        return (0);
    if (str[i] == '|' && str[i + 1] != '|')
        return (1);
    while (str[i + 1] != '\0')
    {
        if (str[i] == '|' && str[i + 1] != '|')
            return (1);
        i++;
    }
    if (str[i] == '|')
        return (1);
    return (0);
}
