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
		ft_init_structures(c_data);
		line_read = (char *)NULL;
		line_read = rl_gets(line_read, c_data->p_data->prompt_text);
		if (!*line_read)
			continue;
		ft_tokenize_expand_input(c_data, line_read);
		if (c_data->q_data->d_open || c_data->q_data->s_open)
			printf("Syntax error: Unclosed quotes\n");
		else
		{
			ft_expansions(c_data);
			// 1 Simple case, no pipes, no redirections
			if (!*(c_data->cmd))
				printf("No cmd provided\n");
			else
			{
				ft_check_cmd(c_data->cmd);
			}
			// 2 Difficult case, with pipes or redirections
		}
		ft_free_quotes_data(c_data);
		ft_free_prompt_data(c_data);
		ft_free_line_data(c_data);
	}
	free(c_data->l_data);
}

// Input collected from user is expanded and tokenized
void	ft_tokenize_expand_input(c_data *c_data, char *line_read)
{
		c_data->q_data->raw_input = ft_strdup(line_read);
		free(line_read);
		ft_tokenize_quotes(c_data->q_data);
		ft_print_linked_list(c_data->q_data);
		printf("\n------------------\n");
}

// First expand quotes, then variables
void    ft_expansions(c_data *c_data)
{
	ft_expand_variables(c_data);
	// Othere expansions here
	c_data->l_data->line_expanded = ft_convert_list_to_str(c_data->q_data);
	printf("Line expanded is |%s|\n", c_data->l_data->line_expanded);
	// printf("%d\n", ft_find_here_marker(c_data->l_data->line_expanded));
	// NESTED LOOP FOR HERE DOCUMENT GOES HERE 
	c_data->cmd = ft_extract_cmd(c_data->l_data->line_expanded);
	printf("Cmd is .%s.\n", c_data->cmd);
}
