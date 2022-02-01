#include "minishell.h"

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

char	*rl_gets(char *line_read, char *prompt_text)
{
	char	*result;

	result = readline(prompt_text);
	if (line_read)
		result = ft_strjoin(line_read, result);
	if (result && *result)
		add_history(result);
	return (result);
}