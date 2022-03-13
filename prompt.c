#include "minishell.h"

/* Collecting input from user */
int		ft_get_valid_input(c_data *c_data, char *prompt_text)
{
	char	*line_read;

	line_read = (char *)NULL;
	line_read = ft_rl_gets(line_read, prompt_text);
	if (!*line_read)
		return (0);
	printf("\n\n--------------------------------------------------------------------------\n");
	printf("                               New input");
	printf("\n--------------------------------------------------------------------------\n\n");
	printf("\033[0;34m");
	printf("Raw input");
	printf("\033[0m");
	printf(":\n\t.%s.\n\n", line_read);
	if (c_data->q_data->raw_input)
		c_data->q_data->raw_input = ft_strjoin(c_data->q_data->raw_input, line_read);
	else
		c_data->q_data->raw_input = ft_strdup(line_read);
	free(line_read);
	return (1);
}

/*  Collecting user input with readline and adding it to history */
char	*ft_rl_gets(char *line_read, char *prompt_text)
{
	char	*result;

	result = readline(prompt_text);
	if (line_read != NULL)
		result = ft_strjoin(line_read, result);
	if (result && *result)
		add_history(result); // TODO This might be moved elsewhere, check for here doc
	return (result);
}

