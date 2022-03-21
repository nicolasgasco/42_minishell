/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:26:32 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:26:35 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Linked list's nodes are deallocated one by one */
void	ft_deallocate_quotes_list(struct s_qnode **quotes_list)
{
	struct s_qnode	*curr;
	struct s_qnode	*aux;

	curr = *quotes_list;
	if (curr == NULL)
		*quotes_list = NULL;
	else
	{
		aux = curr;
		ft_deallocate_quotes_list(&curr->next);
		free(aux->str);
		free(aux);
	}
}

/* Linked list's nodes are deallocated one by one */
void	ft_deallocate_tokens_list(struct s_tnode **token_list)
{
	struct s_tnode	*curr;

	curr = *token_list;
	if (curr == NULL)
		*token_list = NULL;
	else
	{
		ft_deallocate_tokens_list(&curr->next);
		free(curr->str);
		free(curr);
	}
}

void	ft_free_export(t_cdata *t_cdata)
{
	int	i;

	i = 0;
	while (t_cdata->envp_export[i] != NULL)
	{
		free(t_cdata->envp_export[i]);
		i++;
	}
	free(t_cdata->envp_export);
}

void	ft_free_envp(t_cdata *t_cdata)
{
	int	i;

	i = 0;
	while (t_cdata->envp[i] != NULL)
	{
		free(t_cdata->envp[i]);
		i++;
	}
	free(t_cdata->envp);
}
