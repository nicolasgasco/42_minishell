/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:52:45 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:52:46 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* No arguments accepted, global data initialization, loop initialization */
int	main(int argc, char *argv[], char *envp[])
{
	t_cdata	t_cdata;

	if (argc != 1 || argv[1])
	{
		printf("Error: arguments\n");
		return (1);
	}
	ft_init_general_data(&t_cdata, envp);
	ft_start_loop(&t_cdata);
	ft_free_general_data(&t_cdata);
	return (0);
}

/* Input is collected, tokenized, expanded, and sent for processing */
void	ft_start_loop(t_cdata *t_cdata)
{
	while (1)
	{
		ft_init_loot_pdata(t_cdata);
		if (!ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_text)
			&& ft_output_loop_error_message(t_cdata, "Input not valid"))
			continue ;
		ft_here_doc_expansion(t_cdata);
		ft_expand_quotes(t_cdata);
		if (!ft_expanded_quotes_are_valid(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error"))
			continue ;
		ft_expand_spaces(t_cdata);
		ft_expand_variables(t_cdata);
		if (!ft_special_chars_are_valid(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error"))
			continue ;
		if (!ft_remove_empty_nodes(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error"))
			continue ;
		ft_create_tokens_list(t_cdata); // Free?
		ft_check_cmd(t_cdata);
		ft_free_loop_data(t_cdata);
	}
}

void	ft_check_cmd(t_cdata *t_cdata)
{
	t_cdata->cmd = t_cdata->tokens_list->str;
	ft_print_cmd(t_cdata); // TBD
	// if (ft_strncmp(t_cdata->cmd, "echo", 4) == 0)
	// 	built_echo(t_cdata->tokens);
	// else if (ft_strncmp(t_cdata->cmd, "cd", 2) == 0)
	// 	built_cd(t_cdata->tokens[1], t_cdata);
	// else if (ft_strncmp(t_cdata->cmd, "pwd", 3) == 0)
	// 	built_pwd();
	// else if (ft_strncmp(t_cdata->cmd, "export", 6) == 0)
	// 	built_export(t_cdata->tokens + 1, t_cdata);
	// else if (ft_strncmp(t_cdata->cmd, "unset", 5) == 0)
	// 	built_unset(t_cdata->tokens + 1, t_cdata);
	// else if (ft_strncmp(t_cdata->cmd, "env", 3) == 0)
	// 	built_envp(t_cdata);
	// if (ft_strncmp(t_cdata->cmd, "exit", 4) == 0)
	// {
	// 	ft_free_loop_data(t_cdata);
	// 	// ft_free_general_data(t_cdata);
	// 	exit(1);
	// }
	// else
	// 	ft_print_unknown_command();
}
