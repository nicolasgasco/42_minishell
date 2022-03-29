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

int	ft_found_adjacent_special_chars(t_cdata *t_cdata)
{
	struct s_qnode	*curr;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		if (ft_is_special_str(curr->str) && ft_is_special_str(curr->next->str)
			|| ft_found_adjecent_pipes(curr->str))
			return (1);
		if (curr->next == NULL || curr->next->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (0);
}

int	ft_is_special_str(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

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
