#include "minishell.h"

/* No arguments accepted, global data initialization, loop initialization */
int	main(int argc, char *argv[], char *envp[])
{
	c_data c_data;

	if (argc != 1)
	{
		printf("Error: arguments\n");
		return (1);
	}
	ft_init_general_data(&c_data, envp);
	ft_start_loop(&c_data);
	return (0);
}

/* Main loop, input is collected, tokenized, expanded, and sent for processing */
void	ft_start_loop(c_data *c_data)
{
	while (1)
	{
		ft_init_structures(c_data);
		if (ft_input_has_error(c_data) == 1)
			continue ;
		ft_expand_variables(c_data);
		c_data->line_expanded = ft_convert_list_to_str(c_data->q_data);
		ft_print_expanded_output(c_data); // TBD
		if (ft_find_here_marker(c_data->line_expanded))
		{
			printf("A Here document structure was detected\n");
			// TODO nested loop for Here document
		}
		// TODO logic for << and >>
		if (ft_detect_special_characters(c_data))
			ft_print_special_char_detected(); // TBD
		else
		{
			if (c_data->syntax_error)
			{
				ft_print_syntax_error(); // TBD
				continue;
			}
			ft_print_no_special_char_detected(); // TBD
		}
		ft_create_mock_list(c_data, "cmd", "input", "|", "cmd", "input", ""); // TBD Last parameter must be empty line
		ft_print_tokens_list(c_data->tokens_list); // TBD
		c_data->cmd = c_data->tokens_list->str;
		ft_check_cmd(c_data);
		ft_free_loop_data(c_data);
		printf("\n__________________________________________________________________________\n\n");
	}
}

int		ft_input_has_error(c_data *c_data)
{
	if (!ft_get_input(c_data))
		return (1);
	ft_expand_quotes(c_data); // TODO Known issue with simple quotes (issue with start)
	if (c_data->syntax_error)
	{
		ft_print_unclosed_quotes();
		return (1);
	}
	return (0);
}

void    ft_check_cmd(c_data *c_data)
{
	ft_print_cmd(c_data); // TBD
    if (ft_strncmp(c_data->cmd, "echo", 4) == 0)
	    built_echo(c_data->tokens);
    else if (ft_strncmp(c_data->cmd, "cd", 2) == 0)
	    built_cd(c_data->tokens[1], c_data);
    else if (ft_strncmp(c_data->cmd, "pwd", 3) == 0)
	    built_pwd();
    else if (ft_strncmp(c_data->cmd, "export", 6) == 0)
	    built_export(c_data->tokens + 1, c_data);
    else if (ft_strncmp(c_data->cmd, "unset", 5) == 0)
	    built_unset(c_data->tokens + 1, c_data);
    else if (ft_strncmp(c_data->cmd, "env", 3) == 0)
	    built_envp(c_data);
    else if (ft_strncmp(c_data->cmd, "exit", 4) == 0)
        exit(1);
    else
	{
		printf("\033[0;31m");
        printf("Unknown command.\n");
		printf("\033[0m");
	}
}