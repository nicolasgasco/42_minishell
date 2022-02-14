#include "minishell.h"

// The text shown when prompting user for input, e.g. username@hostname
char	*ft_create_prompt_text(char	*username, char *hostname)
{
	int		i;
	int		len1;
	int		len2;
	char	*result;
	
	i = 0;
	len1 = ft_strlen(username);
	len2 = ft_strlen(hostname);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 4));
	while (i < len1)
	{
		result[i] = username[i];
		i++;
	}
	result[i] = '@';
	i++;
	while (i < (len1 + len2 + 1))
	{
		result[i] = hostname[i - len1 - 1];
		i++;
	}
	result[i] = ':';
	result[i + 1] = ' ';
	result[i + 2] = '\0';
	return (result);
}

// readline input, both standalone and being part of a bigger input
char	*rl_gets(char *line_read, char *prompt_text)
{
	char	*result;

	result = readline(prompt_text);
	if (line_read != NULL)
		result = ft_strjoin(line_read, result);
	if (result && *result)
		add_history(result);
	return (result);
}


// Checks if all quotes are properly closed. If not, another prompt is shown
int ft_are_quotes_unclosed(char *line)
{
    int     i;
    int     word_open;

    i = 0;
    word_open = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '\'')
        {
            if (i > 0 && line[i - 1] == '\\')
            {
                if (word_open == 1)
                    word_open = 0;
            }
            else
            {
                if (word_open == 0)
                    word_open = 1;
                else if (word_open == 1)
                    word_open = 0;
            }
        }
        i++;
    }
    return (word_open);
}