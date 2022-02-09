#include "minishell.h"

char    *ft_expand_simple_quotes(char *line)
{
    char    *result;
    int     new_length;
    
    new_length = ft_str_len_unescaped(line, '\'');
    result = malloc(sizeof(char) * (new_length + 1));
    result = ft_expand_escaped_quotes(line, new_length);
    return (result);
}

// Quotes are removed or kept depending if they're escaped inside or outside a set of quotes
char *ft_expand_escaped_quotes(char *line, int length)
{
    int     i;
    int     y;
    int     word_started;
    char    *result;

    ft_expanded_escaped_quotes_init(&i, &y, &word_started);
    result = malloc(sizeof(char) * (length + 1));
    while (line[i] != '\0')
    {
        if (line[i] == '\'')
        {
            if (i > 0 && line[i - 1] == '\\')
            {
                if (word_started == 1)
                    word_started = 0;
                else
                    i--;
            }
            else
                word_started = ft_toggle_word_started(word_started);
            i++;
        }
        if (line[i] == '\\' && word_started == 0)
            i++;
        result[y] = line[i];
        i++;
        y++;
    }
    result[y] = '\0';
    printf("Result: %s\n", result);
    return (result);
}

void    ft_expanded_escaped_quotes_init(int *i, int *y, int *w)
{
    *i = 0;
    *y = 0;
    *w = 0;
}

