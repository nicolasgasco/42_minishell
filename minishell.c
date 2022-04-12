/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:52:45 by ngasco            #+#    #+#             */
/*   Updated: 2022/04/11 11:22:35 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_ex_status;

/* No arguments accepted, global data initialization, loop initialization */
int	main(int argc, char *argv[], char *envp[])
{
	t_cdata	t_cdata;

	if (argc != 1 || argv[1])
	{
		write(2, "Error: arguments\n", 17);
		return (1);
	}
	ft_init_general_data(&t_cdata, envp);
	ft_start_loop(&t_cdata);
	ft_free_general_data(&t_cdata);
	return (0);
}

/* Input is collected, tokenized, expanded, and sent for execution */
void	ft_start_loop(t_cdata *t_cdata)
{	
	while (1)
	{
		ft_shortcut_events();
		ft_init_reset_loop_data(t_cdata);
		if (!ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_text))
			continue ;
		if (!ft_here_doc_expansion(t_cdata) && ft_output_loop_err(t_cdata))
			continue ;
		ft_expand_quotes(t_cdata);
		if (!ft_expanded_quotes_are_valid(t_cdata)
			&& ft_output_loop_err(t_cdata))
			continue ;
		ft_expand_spaces(t_cdata);
		ft_expand_variables(t_cdata);
		ft_expand_special_chars(t_cdata);
		if (!ft_special_chars_are_valid(t_cdata) && ft_output_loop_err(t_cdata))
			continue ;
		if (!ft_remove_empty_nodes(t_cdata))
			continue ;
		ft_start_execution(t_cdata);
		ft_free_loop_data(t_cdata);
	}
}

/* Processed input is executed */
void	ft_start_execution(t_cdata *t_cdata)
{
	t_job	*job;

	job = NULL;
	ft_create_tokens_list(t_cdata);
	printest(t_cdata->tokens_list);
	test(t_cdata->tokens_list);
	job = ft_create_exec(job, t_cdata->tokens_list);
	if (job)
	{
		executor(ms_head_list_job(job), t_cdata);
		free_job_lst(job);
	}
}
