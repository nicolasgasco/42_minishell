#include "minishell.h"

char	*rl_gets(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline(":$ ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}