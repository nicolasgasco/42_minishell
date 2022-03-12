#include "minishell.h"

/* Collecting input from user */
int		ft_get_input(c_data *c_data)
{
	char	*line_read;

	line_read = (char *)NULL;
	line_read = ft_rl_gets(line_read, c_data->p_data->prompt_text);
	if (!*line_read)
		return (0);
	printf("\n\n--------------------------------------------------------------------------\n");
	printf("                          New input");
	printf("\n--------------------------------------------------------------------------\n\n");
	printf("Raw input: .%s.\n", line_read);
	// Known issue with single quotes
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

/* The text shown when prompting user for input, e.g. username@hostname */
char	*ft_create_prompt_text(char *username, char *hostname)
{
	int		i;
	int		len1;
	int		len2;
	char	*result;
	
	i = -1;
	len1 = ft_strlen(username);
	len2 = ft_strlen(hostname);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 4));
	while (++i < len1)
		result[i] = username[i];
	result[i] = '@';
	while (++i < (len1 + len2 + 1))
		result[i] = hostname[i - len1 - 1];
	ft_strlcat(result, ": ", i + 3);
	return (result);
}
