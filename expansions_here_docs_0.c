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
	if (ft_found_lonely_here_marker(t_cdata->t_qdata->raw_input))
	{
		t_cdata->syntax_error = 1;
		return (0);
	}
	if (ft_find_here_marker_str(t_cdata->t_qdata->raw_input))
	{
		t_cdata->found_here_doc = 1;
		// printf(".%s.\n", ft_extract_delim(t_cdata));
		ft_print_here_doc_detected(); // TBD
		if (t_cdata->syntax_error == 1)
			return (0);
	}
	return (1);
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
