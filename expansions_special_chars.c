#include "minishell.h"

// Check if a character is invalid for Here document structure
int ft_found_invalid_character(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"' || c == '!')
        return (1);
    return (0);
}

// Detect if pipes or redirections are present in the user input
char	ft_detect_special_characters(c_data *c_data)
{
	int     i;
    char    *str;

	i = 1;
    str = c_data->line_expanded;
    if (ft_found_special_character(str[0]))
    {
        if (!ft_found_invalid_character(str[1]))
            return (1);
        c_data->syntax_error = 1;
        return (0);
    }
    while (str[i + 1] != '\0')
	{
		if (ft_found_special_character(str[i]))
        {
            if (!ft_found_invalid_character(str[i + 1]) && !ft_found_invalid_character(str[i - 1]))
            return (1);
            c_data->syntax_error = 1;
            return (0);       
        }
        i++;
	}
    if (ft_found_special_character(str[i]))
    {
        if (!ft_found_invalid_character(str[i - 1]))
            return (1);
        c_data->syntax_error = 1;
        return (0);
    }
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