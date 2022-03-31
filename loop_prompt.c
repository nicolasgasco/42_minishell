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
		t_cdata->t_qdata->raw_input = ft_join_append_newline(t_cdata, line_read);
	}
	else
	{
		ft_print_new_input_header(line_read);
		t_cdata->t_qdata->raw_input = ft_strdup(line_read);
	}
	free(line_read);
	return (1);
}

/* Join raw input and line read and append newline */
char	*ft_join_append_newline(t_cdata *t_cdata, char *line_read)
{
	char	*raw_input_temp;

	raw_input_temp = t_cdata->t_qdata->raw_input;
	free(t_cdata->t_qdata->raw_input);
	t_cdata->t_qdata->raw_input = ft_strjoin(raw_input_temp, line_read);
	free(raw_input_temp);
	raw_input_temp = t_cdata->t_qdata->raw_input;
	free(t_cdata->t_qdata->raw_input);
	t_cdata->t_qdata->raw_input = ft_append_newline(raw_input_temp);
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

/* Append newline to string */
char	*ft_append_newline(char *str)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	while (str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
}