#include "minishell.h"

// Accepts user input
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