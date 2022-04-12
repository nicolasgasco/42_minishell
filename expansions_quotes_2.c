/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_quotes_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:00:38 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 12:00:52 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Three cases: quoted string, quoted string but empty, unquoted string */
char	*ft_write_str_to_node(t_qdata *t_qdata, int end)
{
	if (end - t_qdata->start > 1)
		return (ft_create_quoted_token(t_qdata->raw_input,
				t_qdata->start, end - t_qdata->start));
	else
	{
		if (t_qdata->raw_input[t_qdata->start] == '\''
			|| t_qdata->raw_input[t_qdata->start] == '\"')
			return ((ft_create_quoted_token_empty(t_qdata->raw_input,
						t_qdata->start)));
		else
			return (ft_create_unquoted_token(t_qdata->raw_input, t_qdata->start,
					end - t_qdata->start));
	}
}

/* a) Actual token text is written into node ignoring quotes */
char	*ft_create_quoted_token(char *input, int start, int len)
{
	char	*result;
	int		result_len;
	int		i;
	int		y;

	i = start;
	result_len = len;
	y = 0;
	if (input[start] == '\"' || input[start] == '\'')
		i++;
	if (input[start + len] == '\"' || input[start + len] == '\'')
	{
		if (input[start] == '\"' || input[start] == '\'')
			result_len--;
	}
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	while (result_len != 0)
	{
		result[y] = input[i];
		i++;
		y++;
		result_len--;
	}
	result[y] = '\0';
	return (result);
}

/* b) Case where empty set of quotes is given "" */
char	*ft_create_quoted_token_empty(char *input, int start)
{
	char	*result;
	int		i;
	int		y;

	i = start;
	y = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(input) - start - 2 + 1));
	while (i < start)
	{
		result[y] = input[i];
		i++;
		y++;
	}
	result[y] = '\0';
	return (result);
}

/* c) Case where no quote is present */
char	*ft_create_unquoted_token(char *input, int start, int len)
{
	char	*result;
	int		result_len;
	int		i;
	int		y;

	i = start;
	result_len = len;
	y = 0;
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	while (result_len != 0)
	{
		result[y] = input[i];
		i++;
		y++;
		result_len--;
	}
	result[y] = '\0';
	return (result);
}

/* Iterate all nodes of linked lists and concatenate them in a string */
char	*ft_convert_list_to_str(t_qdata *t_qdata)
{
	struct s_qnode	*curr;
	char			*result;
	int				i;

	i = 0;
	result = NULL;
	curr = t_qdata->quotes_list;
	while (1)
	{
		if (result == NULL)
			result = ft_strdup(curr->str);
		else
			result = ft_strcat(result, curr->str);
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
		i++;
	}
	return (result);
}
