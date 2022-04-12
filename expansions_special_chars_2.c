/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_special_chars_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:36:09 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/29 11:36:11 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Adding new nodes with the single parts of the split string with s char */
void	ft_add_special_char_nodes(struct s_qnode *curr,
			char *curr_str, char *next_str, char *rest)
{
	struct s_qnode	*new_node1;

	new_node1 = (struct s_qnode *)malloc(sizeof(struct s_qnode));
	memset(new_node1, 0, sizeof(struct s_qnode));
	free(curr->str);
	curr->str = curr_str;
	curr->length = ft_strlen(curr_str);
	new_node1->str = next_str;
	new_node1->length = ft_strlen(new_node1->str);
	if (*rest)
	{
		ft_populate_new_node_2(new_node1, curr, rest);
		curr->is_spaced = 0;
		new_node1->is_spaced = 0;
	}
	else
	{
		new_node1->next = curr->next;
		new_node1->is_spaced = curr->is_spaced;
		curr->is_spaced = 0;
		free(rest);
	}
	curr->next = new_node1;
}

void	ft_populate_new_node_2(struct s_qnode *new_node1,
			struct s_qnode *curr, char *rest)
{
	struct s_qnode	*new_node2;

	new_node2 = (struct s_qnode *)malloc(sizeof(struct s_qnode));
	memset(new_node2, 0, sizeof(struct s_qnode));
	new_node2->str = rest;
	new_node2->length = ft_strlen(new_node2->str);
	new_node2->next = curr->next;
	new_node2->is_spaced = curr->is_spaced;
	new_node1->next = new_node2;
}
