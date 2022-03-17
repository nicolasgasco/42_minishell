#include "minishell.h"

/* No arguments accepted, global data initialization, loop initialization */
int	main(int argc, char *argv[], char *envp[])
{
	t_cdata t_cdata;

	if (argc != 1 || argv[1])
	{
		printf("Error: arguments\n");
		return (1);
	}
	ft_init_general_data(&t_cdata, envp);
	ft_start_loop(&t_cdata);
	return (0);
}

/* Main loop, input is collected, tokenized, expanded, and sent for processing */
void	ft_start_loop(t_cdata *t_cdata)
{
	while (1)
	{
		ft_init_loot_pdata(t_cdata);
		if (!ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_text))
		{
			ft_free_quotes_data(t_cdata);
			continue ;
		}
		ft_expand_quotes(t_cdata);
		ft_expand_spaces(t_cdata);
		if (!ft_expanded_quotes_are_valid(t_cdata))
		{
			ft_free_loop_data_quotes_error(t_cdata);
			continue ;
		}
		ft_expand_special_chars(t_cdata);
		ft_expand_variables(t_cdata);
		// if (ft_find_here_marker_list(t_cdata))
		// 	ft_here_doc_loop(t_cdata);
		t_cdata->line_expanded = ft_convert_list_to_str(t_cdata->t_qdata);
		ft_print_expanded_output(t_cdata); // TBD
		// if (!ft_special_chars_are_valid(t_cdata))
		// 	continue;
		// ft_create_tokens_list(t_cdata);
		ft_create_mock_list(t_cdata, "cmd", "holla", "que", "tal", "|", "cmd", "input", ""); // TBD Last parameter must be empty line
		ft_print_tokens_list(t_cdata->tokens_list); // TBD
		// ft_check_cmd(t_cdata);
		ft_free_loop_data(t_cdata);
		printf("\n__________________________________________________________________________\n\n");
	}
}

void    ft_check_cmd(t_cdata *t_cdata)
{
	t_cdata->cmd = t_cdata->tokens_list->str;
	ft_print_cmd(t_cdata); // TBD
    if (ft_strncmp(t_cdata->cmd, "echo", 4) == 0)
	    built_echo(t_cdata->tokens);
    else if (ft_strncmp(t_cdata->cmd, "cd", 2) == 0)
	    built_cd(t_cdata->tokens[1], t_cdata);
    else if (ft_strncmp(t_cdata->cmd, "pwd", 3) == 0)
	    built_pwd();
    else if (ft_strncmp(t_cdata->cmd, "export", 6) == 0)
	    built_export(t_cdata->tokens + 1, t_cdata);
    else if (ft_strncmp(t_cdata->cmd, "unset", 5) == 0)
	    built_unset(t_cdata->tokens + 1, t_cdata);
    else if (ft_strncmp(t_cdata->cmd, "env", 3) == 0)
	    built_envp(t_cdata);
    if (ft_strncmp(t_cdata->cmd, "exit", 4) == 0)
	{
		ft_free_loop_data(t_cdata);
		// ft_free_general_data(t_cdata);
        exit(1);
	}
	else
		ft_print_unknown_command();
}