/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:01:13 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:01:15 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_tokens_list(t_cdata *t_cdata)
{
	struct s_qnode	*curr;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		ft_add_token_to_list(t_cdata, curr);
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	if (!ft_strcmp(t_cdata->tokens_list->str, "export"))
	{
		while (1)
		{
			if (!ft_find_quoted_vars(t_cdata))
				break ;
		}
	}
}

void	ft_add_token_to_list(t_cdata *t_cdata, struct s_qnode *origin)
{
	struct s_tnode	*new_node;
	struct s_tnode	*curr;

	curr = t_cdata->tokens_list;
	new_node = (struct s_tnode *)malloc(sizeof(struct s_tnode));
	memset(new_node, 0, sizeof(struct s_tnode));
	if (new_node == NULL)
		exit(1);
	new_node->str = ft_strdup(origin->str);
	new_node->len = ft_strlen(origin->str);
	new_node->q_type = origin->q_type;
	new_node->is_spaced = origin->is_spaced;
	new_node->next = NULL;
	while (curr && curr->next != NULL)
		curr = curr->next;
	if (curr)
	{
		new_node->prev = curr;
		curr->next = new_node;
	}
	else
	{
		new_node->prev = NULL;
		t_cdata->tokens_list = new_node;
	}
}
