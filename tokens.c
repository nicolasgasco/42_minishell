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
		ft_add_token_to_list(t_cdata, curr->str);
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	ft_print_tokens_list(t_cdata->tokens_list); // TBD
}

void	ft_add_token_to_list(t_cdata *t_cdata, char *s)
{
	struct s_tnode	*new_node;
	struct s_tnode	*curr;

	curr = t_cdata->tokens_list;
	new_node = (struct s_tnode *)malloc(sizeof(struct s_tnode));
	if (new_node == NULL)
		exit(1);
	new_node->str = ft_strdup(s);
	new_node->len = ft_strlen(s);
	new_node->next = NULL;
	while (curr && curr->next != NULL)
		curr = curr->next;
	if (curr)
		curr->next = new_node;
	else
		t_cdata->tokens_list = new_node;
}
