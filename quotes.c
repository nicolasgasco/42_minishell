#include "minishell.h"

int ft_isquote(char c)
{
    if (c == 34 || c == 39)
        return (1);
    return (0);
}

int ft_expand_simple_quotes(char *line)
{
    int i;
    int word_open;

    i = 0;
    word_open = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '\'')
        {
            if (i > 0 && line[i - 1] == '\\')
            {
                if (word_open == 0)
                    line = ft_remove_char_index(i - 1, line);
                else if (word_open == 1)
                {
                    line = ft_remove_char_index(i, line);
                    word_open = 0;
                }
                if (line[i] == '\'')
                {
                    line = ft_remove_char_index(i, line);
                    if (word_open == 0)
                        word_open = 1;
                    else if (word_open == 1)
                        word_open = 0;
                }
            }
            else
            {
                line = ft_remove_char_index(i, line);
                if (word_open == 0)
                    word_open = 1;
                else if (word_open == 1)
                    word_open = 0;
            }
            i--;
        }
        i++;
    }
    return (word_open);
}

// Function that interprets quotes
void ft_expand_quotes(char *line)
{
    int i;
    // int quote_count;

    i = 0;
    // quote_count = 0;
    while (line[i] != '\0')
    {
        if (ft_isquote(line[i]) == 1)
            break;
        i++;
    }
    if (line[i] == '\'')
    {
        if (ft_expand_simple_quotes(line) == 1)
        {
            printf("%s\n", line);
            printf("Open quotes oh no\n");
        }
        else
        {
            printf("Closed quotes\n");
        }
    }
    else
        printf("First quote is %c\n", line[i]);
    // printf("%s\n", line);
}

// Look for opening quote and check if it's closed or not
int ft_are_quotes_even(char *line)
{
    int i;
    char open_char;
    int counter;

    i = 0;
    counter = 0;
    while (line[i] != '\0')
    {
        if (ft_isquote(line[i]) == 1)
        {
            counter++;
            break;
        }
        i++;
    }
    open_char = line[i];
    i++;
    while (line[i] != '\0')
    {
        if (line[i] == open_char)
            counter++;
        i++;
    }
    if (counter % 2 == 0)
        return (1);
    return (0);
}
