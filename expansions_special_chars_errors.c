/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_special_chars_errors.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:26:03 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/29 15:26:04 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if two adjacent nodes are both special chars */
int	ft_found_adjacent_special_chars(t_cdata *t_cdata)
{
	struct s_qnode	*curr;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		if (curr->next)
		{
			if (ft_is_special_str(curr->str)
				&& ft_is_special_str(curr->next->str)
				|| ft_found_adjecent_pipes(curr->str))
				return (1);
		}
		if (curr->next == NULL || curr->next->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (0);
}

/* Check if node contains special char */
int	ft_is_special_str(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

/* Check if string contains two pipes */
int	ft_found_adjecent_pipes(char *str)
{
	int	i;

	i = 0;
	if (!ft_strlen(str))
		return (0);
	while (str[i + 1] != '\0')
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

/* Check if list has only one node and it's a special char */
int	ft_last_node_is_special_char(t_cdata *t_cdata)
{
	struct s_qnode	*curr;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		if (curr->next == NULL && ft_is_special_str(curr->str))
			return (1);
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (0);
}
