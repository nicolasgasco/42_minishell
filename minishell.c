/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:52:45 by ngasco            #+#    #+#             */
/*   Updated: 2022/04/05 13:45:41 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

FILE	*output;

/* No arguments accepted, global data initialization, loop initialization */
int	main(int argc, char *argv[], char *envp[])
{
	t_cdata	t_cdata;

	ft_init_general_data(&t_cdata, envp);
	output = fopen("output.txt", "w+");
	fprintf(output, "Opening file for writing output.\n\n");
	fflush(output);
	ft_shortcut_events();
	ft_start_loop(&t_cdata, argv[2]);
	ft_free_general_data(&t_cdata);
	fclose(output);
	return (0);
}

/* Input is collected, tokenized, expanded, and sent for execution */
void	ft_start_loop(t_cdata *t_cdata, char *line)
{
	while (1)
	{
		ft_init_reset_loop_data(t_cdata);
		// if (!ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_text)
		// 	&& ft_output_loop_error_message(t_cdata, "Invalid input"))
		// 	continue ;
		t_cdata->t_qdata->raw_input = ft_strdup(line);
		if (!ft_here_doc_expansion(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error (h. doc)"))
			continue ;
		ft_expand_quotes(t_cdata);
		if (!ft_expanded_quotes_are_valid(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error (quotes)"))
			continue ;
		ft_expand_spaces(t_cdata);
		ft_expand_variables(t_cdata);
		ft_expand_special_chars(t_cdata);
		if (!ft_special_chars_are_valid(t_cdata)
			&& ft_output_loop_error_message(t_cdata, "Syntax error (s. chars)"))
			continue ;
		if (!ft_remove_empty_nodes(t_cdata)
			&& ft_output_loop_error_message(t_cdata, ""))
			continue ;
		ft_start_execution(t_cdata);
		ft_free_loop_data(t_cdata);
		break ;
	}
}

/* Processed input is executed */
void	ft_start_execution(t_cdata *t_cdata)
{
	t_job	*job;

	fflush(output); // TBD
	ft_create_tokens_list(t_cdata); // Free?
	printest(t_cdata->tokens_list);
	test(t_cdata->tokens_list);
	job = ft_create_exec(job, t_cdata->tokens_list);
	if (job)
	{
		executor(ms_head_list_job(job), t_cdata);
		free_job_lst(job);
	}
	fflush(output); // TBD
}
