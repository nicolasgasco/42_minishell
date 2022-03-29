/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:03:16 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 12:03:17 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_sdata sig_data;

/* Collecting input from user: fresh input and repeated input of Here docs */
int	ft_get_valid_input(t_cdata *t_cdata, char *prompt_text)
{
	char	*line_read;
	char	*delim;

	delim = t_cdata->t_qdata->delim;
	line_read = (char *) NULL;
	line_read = ft_rl_gets(line_read, prompt_text);
	if (!*line_read)
	{
		ft_print_new_input_header(line_read); // TBD
		free(line_read);
		return (0);
	}
	if (t_cdata->t_qdata->raw_input)
	{
		if (!ft_strncmp(line_read, delim, ft_strlen(delim))
		&& ft_strlen(line_read) == ft_strlen(delim))
			return (0);
		t_cdata->t_qdata->raw_input = ft_strjoin(t_cdata->t_qdata->raw_input, line_read);
		t_cdata->t_qdata->raw_input = ft_append_newline(t_cdata->t_qdata->raw_input);
	}
	else
	{
		ft_print_new_input_header(line_read);
		t_cdata->t_qdata->raw_input = ft_strdup(line_read);
	}
	free(line_read);
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

char	*ft_append_newline(char *raw_input)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * ft_strlen(raw_input) + 2);
	i = 0;
	while (raw_input[i] != '\0')
	{
		result[i] = raw_input[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	free(raw_input);
	return (result);
}