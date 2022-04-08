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
void	ft_find_quoted_vars(struct s_tnode *curr)
{
	while (1)
	{
		if (curr->str[curr->len - 1] == '=')
		{
			if (curr->next)
				ft_join_var_name_value(curr);
		}
		if (curr->next == NULL)
		{
			break;
		}
		curr = curr->next;
	}
}

/* Join the two nodes making up the env var declaration */
void	ft_join_var_name_value(struct s_tnode *curr)
{
	char			*str_temp;
	struct s_tnode	*node_temp;

	str_temp = ft_strjoin(curr->str, curr->next->str);
	free(curr->str);
	curr->str = str_temp;
	node_temp = curr->next;
	curr->next = curr->next->next;
	free(node_temp->str);
	free(node_temp);
}
