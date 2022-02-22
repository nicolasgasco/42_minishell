#include "minishell.h"

// No arguments accepted, global data initialization, loop initialization
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
	while (1)
	{
		ft_init_structures(c_data);
		if (!ft_get_input(c_data))
			continue ;
		ft_expand_quotes(c_data); // TODO Known issue with simple quotes (issue with start)
		if (c_data->syntax_error)
		{
			printf("Syntax error: Unclosed quotes\n");
			printf("\n__________________________________________________________________________\n\n");
			continue ;
		}
		ft_expand_variables(c_data);
		c_data->line_expanded = ft_convert_list_to_str(c_data->q_data);
		printf("Expanded input: .%s.\n", c_data->line_expanded);
		if (ft_find_here_marker(c_data->line_expanded))
		{
			printf("A Here document structure was detected\n");
			// TODO nested loop for Here document
		}
		// Todo logic for << and >>
		if (ft_detect_special_characters(c_data))
			printf("A special character was detected.\n");
		else
		{
			if (c_data->syntax_error)
			{
				printf("Syntax error.\n");
				printf("\n__________________________________________________________________________\n\n");
				continue;
			}
			printf("No special character was detected.\n");
		}
		ft_create_mock_list(c_data, "cmd", "input", "|", "cmd", "input", ""); // Last parameter must be empty line
		ft_print_tokens_list(c_data->tokens_list);
		c_data->cmd = c_data->tokens_list->str;
		printf("Command: .%s.\n", c_data->cmd);
		ft_check_cmd(c_data->cmd);
		ft_free_loop_data(c_data);
		printf("\n__________________________________________________________________________\n\n");
	}
}
