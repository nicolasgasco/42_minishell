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

/* Initialize Here doc loop, if any */
int	ft_here_doc_expansion(t_cdata *t_cdata)
{
	if (ft_found_empty_here_marker(t_cdata->t_qdata->raw_input))
	{
		t_cdata->syntax_error = 1;
		return (0);
	}
	if (!ft_find_here_marker_str(t_cdata->t_qdata->raw_input))
	{
		ft_print_here_doc_detected(); // TBD
		ft_here_doc_loop(t_cdata);
	}
	return (1);
}

/* Checks for case when input is just << with no content */
int	ft_found_empty_here_marker(char *str)
{
	char	*temp;

	temp = ft_strtrim(str, "\n\t ");
	if (ft_strcmp(temp, "<<") == 0)
	{
		free(temp);
		return (1);
	}
	return (0);
}

/* Look for Here document in a string */
int	ft_find_here_marker_str(char *str)
{
	int	i;
	int	found_quote;

	i = 1;
	found_quote = 0;
	if (ft_strlen(str) < 4)
		return (0);
	while (str[i + 2] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (found_quote)
				found_quote = 0;
			else
				found_quote = 1;
		}
		if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<'
			&& str[i + 2] != '|' && str[i + 2] != '<' && str[i + 2] != '>'
			&& !found_quote)
			return (1);
		i++;
	}
	if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] != '<' && !found_quote)
		return (1);
	return (0);
}

/* Initialize loop to collect input untill delimiter is found */
void	ft_here_doc_loop(t_cdata *t_cdata)
{
	int	i;

	i = 0;
	t_cdata->t_qdata->delim = ft_extract_and_remove_delim(t_cdata);
	while (1)
	{
		if (!ft_get_valid_input(t_cdata, t_cdata->t_pdata->prompt_nl_text))
			break ;
		i++;
	}
}

/* Save delimiter in variable and remove it from raw input */
char	*ft_extract_and_remove_delim(t_cdata *t_cdata)
{
	int		i;
	char	*result;
	char	*raw_input;
	char	*raw_input_temp;

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
	result = ft_substr(raw_input, i, ft_strlen(raw_input) - i);
	if (ft_has_spaces(result))
		result = ft_strtrim(result, " \t"); // Check
	raw_input_temp = ft_substr(raw_input, 0, i);
	free(t_cdata->t_qdata->raw_input);
	t_cdata->t_qdata->raw_input = raw_input_temp;
	return (result);
}
