#include "minishell.h"

// No arguments accepted, structures initialization, loop initialization
int	main(int argc, char *argv[], char *envp[])
{
	c_data c_data;

	if (argc != 1 || argv[1])
	{
		printf("Error: arguments\n");
		return (1);
	}
	ft_init_common_data(&c_data, envp);
	ft_start_loop(&c_data);
	return (0);
}

// Main loop, input is collected, tokenized, expanded, and sent for processing
void	ft_start_loop(c_data *c_data)
{
	char	*line_read;

	while (1)
	{
		line_read = (char *)NULL;
		line_read = rl_gets(line_read, c_data->p_data->prompt_text);
		ft_tokenize_expand_input(c_data, line_read);
		if (c_data->q_data->d_open || c_data->q_data->s_open)
		{
			printf("Invalid output: unclosed quotes\n");
		}
		else
		{
			ft_expansions(c_data);
			// Nested loop here 
			c_data->line_expanded = ft_convert_list_to_str(c_data->q_data);
			printf("Line expanded is |%s|\n", c_data->line_expanded);
			c_data->paths = ft_splitc(getenv("PATH"), ':');
			ft_extract_cmd(c_data);
			ft_check_cmd(c_data->cmd);
		}
	}
}

// Input collected from user is expanded and tokenized
void	ft_tokenize_expand_input(c_data *c_data, char *line_read)
{
		ft_init_quotes_data(c_data);
		c_data->q_data->raw_input = ft_strdup(line_read);
		free(line_read);
		ft_tokenize_quotes(c_data->q_data);
		printf("\n------------------\n");
}