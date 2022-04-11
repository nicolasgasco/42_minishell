/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_here_docs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:44:07 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:44:09 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Isolate delimiter from raw input */
char	*ft_extract_delim(t_cdata *t_cdata)
{
	int		i;
	char	*raw_input;

	raw_input = t_cdata->t_qdata->raw_input;
	i = 0;
	while (t_cdata->t_qdata->raw_input[i + 1] != '\0')
	{
		if (t_cdata->t_qdata->raw_input[i] == '<'
			&& t_cdata->t_qdata->raw_input[i] == '<')
		{
			i += 2;
			break ;
		}
		i++;
	}
	return (ft_remove_delim(t_cdata, i));
}

/* Remove delimiter from raw input */
char	*ft_remove_delim(t_cdata *t_cdata, int del_start)
{
	char	*result;
	char	*raw_input;
	char	*after_delim;
	char	*delim_temp;
	int		del_end;

	raw_input = t_cdata->t_qdata->raw_input;
	del_end = ft_calc_delimiter_end(raw_input, del_start);
	result = ft_substr(raw_input, del_start, del_end - del_start);
	after_delim = ft_substr(raw_input, del_end, ft_strlen(raw_input) - del_end);
	t_cdata->t_qdata->after_delim = after_delim;
	delim_temp = result;
	if (ft_has_spaces(result))
	{
		result = ft_strtrim(result, " \t");
		free(delim_temp);
	}
	ft_remove_delim_from_raw_input(t_cdata, del_start);
	return (result);
}

void	ft_remove_delim_from_raw_input(t_cdata *t_cdata, int delimiter_start)
{
	char	*raw_input_temp;
	char	*raw_input;

	raw_input = t_cdata->t_qdata->raw_input;
	raw_input_temp = ft_substr(raw_input, 0, delimiter_start);
	free(t_cdata->t_qdata->raw_input);
	t_cdata->t_qdata->raw_input = raw_input_temp;
}

int	ft_calc_delimiter_end(char *raw_input, int start)
{
	int	i;

	i = start;
	while (raw_input[i] != '\0')
	{
		if (raw_input[i] == '>' || raw_input[i] == '<' || raw_input[i] == '|')
			return (i);
		i++;
	}
	return (i);
}
