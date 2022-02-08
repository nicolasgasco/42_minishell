#include "minishell.h"

int	ft_isquote(char	c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

// If first quote is escaped, it is reduced to literal value and ignored
int ft_first_unescaped_quote(char *line)
{
    int i;

    i = 0;
    while(line[i] != '\0')
    {
        if (ft_isquote(line[i]) && i > 0 && line[i - 1] != '\\')
            return (i);
        i++;
    }
    return (0);
}

// Function that interprets quotes
void    ft_expand_quotes(char *line, int start)
{
    int i;
    int quote_count;

    i = start;
    quote_count = 0;
    printf("start is %d\n", start);
    while (line[i] != '\0')
    {
        if (ft_isquote(line[i]) == 1)
            break;
        i++;
    }
    if (line[i] == '\'')
    {
        quote_count = ft_count_char(line[i], line, start);
        printf("First quote is %c\n", line[i]);
        if ((quote_count % 2) == 0)
        {
            printf("Even number of quotes -> trimming\n");
            line = ft_remove_char(line[i], line, start);
            line = ft_remove_char('\\', line, 0);
            printf("Trimmed line %s\n", line);
        }
        else
            printf("Odd number of quotes -> open prompt\n");
    }
    else
        printf("First quote is %c\n", line[i]);
    // printf("%s\n", line);
}

// Look for opening quote and check if it's closed or not
int ft_are_quotes_even(char *line)
{
	int 	i;
	char 	open_char;
	int		counter;

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
