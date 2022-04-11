/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_special_chars_0.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:54:43 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:54:44 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_join_spaceless_nodes(t_cdata *t_cdata)
{
	while (1)
	{
		if (ft_found_spaceless_nodes(t_cdata) == 0)
			break ;
	}
}

int	ft_found_spaceless_nodes(t_cdata *t_cdata)
{
	struct s_qnode	*curr;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		if (curr->next)
		{
			if (!curr->is_spaced && !ft_found_one_special_char(curr->str)
					&& !ft_found_one_special_char(curr->next->str))
			{
				ft_join_nodes(curr);
				return (1);
			}
		}
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	return (0);
}

void	ft_join_nodes(struct s_qnode *curr)
{
	char			*temp;
	struct s_qnode	*node_temp;

	temp = ft_strdup(curr->str);
	free(curr->str);
	curr->str = ft_strjoin(temp, curr->next->str);
	free(temp);
	curr->is_spaced = curr->next->is_spaced;
	curr->length = ft_strlen(curr->str);
	curr->q_type = '\0';
	node_temp = curr->next;
	if (!curr->next->next)
		curr->next = NULL;
	else
		curr->next = curr->next->next;
	free(node_temp->str);
	free(node_temp);
}
