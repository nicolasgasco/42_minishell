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
	t_job *job;

	while (1)
	{
		ft_init_reset_loop_data(t_cdata);
		if (!ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_text)
			&& ft_output_loop_error_message(t_cdata, "Invalid input"))
			continue ;
		if (!ft_here_doc_expansion(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error (here doc)"))
			continue ;
		ft_expand_quotes(t_cdata);
		if (!ft_expanded_quotes_are_valid(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error (quotes)"))
			continue ;
		ft_expand_spaces(t_cdata);
		ft_expand_variables(t_cdata);
		if (!ft_special_chars_are_valid(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error (special chars)"))
			continue ;
		if (!ft_remove_empty_nodes(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error (empty nodes)"))
			continue ;
		ft_create_tokens_list(t_cdata); // Free?
		printest(t_cdata->tokens_list);
		test(t_cdata->tokens_list);
		tester(t_cdata->tokens_list);
		job = ft_create_exec(job, t_cdata->tokens_list);
		if(job)
		{
			printf("entra en executor\n");
			executor(ms_head_list_job(job), t_cdata);
		}

//		ft_check_cmd(t_cdata);
		ft_free_loop_data(t_cdata);
	}
}
