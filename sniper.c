/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:30:14 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/05 13:34:23 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printest(struct s_tnode *tnode)
{
	while (tnode)
	{
		tnode->type = STRING;
		tnode = tnode->next;
	}
}

void	test(struct s_tnode *tnode)
{
	while (tnode)
	{
		if (!tnode->q_type)
		{	
			if (tnode->str[0] == '|')
				tnode->type = PIPE;
			else if (tnode->str[0] == '<' && tnode->str[1] == '<')
				tnode->type = HEREDOC_L;
			else if (tnode->str[0] == '<')
				tnode->type = REDIR_L;
			else if (tnode->str[0] == '>' && tnode->str[1] == '>')
				tnode->type = APPEND;
			else if (tnode->str[0] == '>')
				tnode->type = REDIR_R;
		}
		tnode = tnode->next;
	}
}
