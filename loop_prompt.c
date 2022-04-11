/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:03:16 by ngasco            #+#    #+#             */
/*   Updated: 2022/04/11 11:42:40 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Collecting input from user: fresh input and repeated input of Here docs */
int	ft_get_valid_input(t_cdata *t_cdata, char *prompt_text)
{
	char	*line_read;

	line_read = (char *) NULL;
	line_read = ft_rl_gets(line_read, prompt_text);
	if (!line_read)
	{
		ft_free_quotes_data(t_cdata);
		ft_free_general_data(t_cdata);
		printf("exit\n");
		fclose(output);
		exit(g_ex_status);
	}
	ft_print_new_input_header(line_read); // TBD
	t_cdata->t_qdata->raw_input = ft_strdup(line_read);
	free(line_read);
	if (!*(t_cdata->t_qdata->raw_input))
	{
		ft_free_quotes_data(t_cdata);
		return (0);
	}
	return (1);
}

/*  Collecting user input with readline and adding it to history */
char	*ft_rl_gets(char *line_read, char *prompt_text)
{
	char	*result;

	result = readline(prompt_text);
	if (line_read != NULL)
		result = ft_strjoin(line_read, result);
	if (result && *result)
		add_history(result);
	return (result);
}
