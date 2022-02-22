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
			continue ;
		printf("\n\n-------------------------------------\n");
		printf("               New input            ");
		printf("\n-------------------------------------\n\n");
		printf("Raw input: .%s.\n", line_read);
		ft_expand_quotes(c_data, line_read);
		if (c_data->syntax_error)
		{
			printf("Syntax error: Unclosed quotes\n");
			printf("\n_____________________________________\n\n");
			continue ;
		}
		ft_expand_variables(c_data);
		// Other expansions (if any) here
		c_data->l_data->line_expanded = ft_convert_list_to_str(c_data->q_data);
		printf("Expanded input: .%s.\n", c_data->l_data->line_expanded);
		if (ft_find_here_marker(c_data->l_data->line_expanded))
		{
			printf("A Here document structure was detected\n");
			// NESTED LOOP FOR HERE DOCUMENT GOES HERE 
			// END OF NESTED LOOP
		}
		if (ft_detect_special_characters(c_data))
		{
			printf("A special character was detected.\n");
			// LOGIC FOR PIPES OR REDIRECTIONS HERE (LINKED LIST)
			ft_create_mock_list(c_data, "cmd", "input", "|", "cmd", "input", ""); // Last parameter must be empty line
			ft_print_tokens_list(c_data->tokens_list);
		}
		else
		{
			if (c_data->syntax_error)
			{
				printf("Syntax error.\n");
				printf("\n_____________________________________\n\n");
				continue;
			}
			printf("No special character was detected.\n");
			c_data->cmd = ft_extract_cmd(c_data->l_data->line_expanded);
			printf("Command: .%s.\n", c_data->cmd);
			printf("\n\n");
			// LOGIC FOR SIMPLE CASES HERE (STR)
			ft_check_cmd(c_data->cmd);
			// Create tokens (str) here
		}
		// Things that must be freed at every cycle
		// FREE TOKENS
		ft_free_quotes_data(c_data);
		ft_free_prompt_data(c_data);
		ft_free_line_data(c_data);
		ft_deallocate_tokens_list(&c_data->tokens_list);
		printf("\n_____________________________________\n\n");
	}
	// Things that must be freed when program is over
	free(c_data->l_data);
}

// User input is tokenized according to quotes to see if they're unclosed or not
void	ft_expand_quotes(c_data *c_data, char *line_read)
{
	// Known issue with single quotes
	c_data->q_data->raw_input = ft_strdup(line_read);
	free(line_read);
	ft_tokenize_quotes(c_data->q_data);
	printf("Quotes linked list: ");
	ft_print_quotes_list(c_data->q_data->quotes_list);
	if (c_data->q_data->d_open || c_data->q_data->s_open)
		c_data->syntax_error = 1;
}
