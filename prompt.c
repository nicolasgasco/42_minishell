#include "minishell.h"

char	*rl_gets(char *line_read, char *prompt_text)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline(prompt_text);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}