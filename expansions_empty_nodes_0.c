/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_empty_nodes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:14:01 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:14:02 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_remove_empty_nodes(t_cdata *t_cdata)
{
	int	result;

	while (1)
	{
		result = ft_found_empty_node_to_remove(t_cdata);
		if (result == 0)
			break ;
		else if (result == -1)
			return (0);
	}
	return (1);
}

/* Removing a single node contaning an empty string */
int	ft_found_empty_node_to_remove(t_cdata *t_cdata)
{
	struct s_qnode	*curr;
	int				i;
	int				found_cmd;

	i = 0;
	found_cmd = 0;
	curr = t_cdata->t_qdata->quotes_list;
	if (!*(curr->str) && curr->next == NULL)
		return (ft_found_empty_node_to_remove_lonely_node(t_cdata, curr));
	while (1)
	{
		if (*(curr->str) && !found_cmd)
			found_cmd = 1;
		else if (!*(curr->str) && (!curr->q_type || !curr->is_spaced)
			&& curr->next)
			return (ft_remove_node_with_index(i,
					&t_cdata->t_qdata->quotes_list));
		if (curr->next == NULL)
			break ;
		curr = curr->next;
		i++;
	}
	return (0);
}

int	ft_found_empty_node_to_remove_lonely_node(t_cdata *t_cdata,
	struct s_qnode *curr)
{
	if (!curr->q_type)
	{
		t_cdata->syntax_error = 1 ;
		return (-1);
	}
	return (0);
}

int	ft_remove_node_with_index(int index, struct s_qnode **root)
{
	struct s_qnode	*curr;
	struct s_qnode	*to_remove;
	int				i;

	i = 1;
	curr = *root;
	if (*root == NULL)
		return (1);
	if (index == 0)
	{
		to_remove = *root;
		*root = (*root)->next;
		ft_remove_node_with_index_free_util(to_remove);
		return (1);
	}
	while (i < index)
	{
		curr = curr->next;
		i++;
	}
	to_remove = curr->next;
	curr->next = curr->next->next;
	ft_remove_node_with_index_free_util(to_remove);
	return (1);
}

/* Util function to shorten function above */
void	ft_remove_node_with_index_free_util(struct s_qnode *to_remove)
{
	free(to_remove->str);
	free(to_remove);
}
