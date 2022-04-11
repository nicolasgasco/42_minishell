/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_vars_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:27:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:27:51 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Look for env vars declarations separated by quotes expansion */
int	ft_find_quoted_vars(t_cdata *t_cdata)
{
	struct s_tnode	*curr;

	curr = t_cdata->tokens_list;
	while (1)
	{
		if (curr->str[curr->len - 1] == '=')
		{
			if (curr->next)
			{
				ft_join_var_name_value(curr);
				return (1);
			}
		}
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (0);
}

/* Join the two nodes making up the env var declaration */
void	ft_join_var_name_value(struct s_tnode *curr)
{
	char			*str_temp;
	struct s_tnode	*node_temp;

	str_temp = ft_strjoin(curr->str, curr->next->str);
	free(curr->str);
	curr->str = str_temp;
	curr->len = ft_strlen(str_temp);
	if (curr->next->next)
		node_temp = curr->next->next;
	else
		node_temp = NULL;
	if (node_temp)
		node_temp->prev = curr;
	free(curr->next->str);
	free(curr->next);
	curr->next = node_temp;
}
