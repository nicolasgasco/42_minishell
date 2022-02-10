#include "minishell.h"

int ft_isquote(char c)
{
    if (c == 34 || c == 39)
        return (1);
    return (0);
}

// int	ft_isspace(char	c)
// {
// 	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
// 		return (1);
// 	return (0);
// }

// Escaped quotes are not valid and must be ignored
int ft_first_valid_quote(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (ft_isquote(line[i]))
            break;
        else if (ft_isquote(line[i]) == 1 && i > 0 && line[i - 1] != '\\')
            break;
        i++;
    }
    return (i);
}

// Calculating length of string once all quotes are correctly expanded and removed
int ft_str_len_unescaped(char *line, char c)
{
    int     i;
    int     word_started;
    int     counter;

    i = 0;
    counter = ft_strlen(line);
    word_started = 0;
    while (line[i] != '\0')
    {
        if (line[i] == c)
        {
            if (i > 0 && line[i - 1] == '\\')
            {
                if (word_started == 0)
                    word_started = 0;
                else
                    counter--;
            }
            else
                word_started = ft_toggle_word_started(word_started);
            counter--;
        }
        i++;
    }
    return (counter);
}

int ft_toggle_word_started(int word_started)
{
    if (word_started == 0)
        return (1);
    else if (word_started == 1)
        return (0);
    return (0);
}