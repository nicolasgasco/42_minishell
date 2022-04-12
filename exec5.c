/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:42:50 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 10:25:20 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(struct s_tnode *token)
{
	if (token->type == REDIR_L || token->type == REDIR_R
		|| token->type == APPEND || token->type == HEREDOC_L)
		return (true);
	return (false);
}

int	counter_string(struct s_tnode *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		else if (tok->type == REDIR_L || tok->type == REDIR_R
			|| tok->type == APPEND || tok->type == HEREDOC_L)
			tok = tok->next;
		else if (tok->type == STRING)
			i++;
		tok = tok->next;
	}
	return (i);
}

void	free_ex(t_job *job, t_cdata *c_data)
{
	ft_free_tab(c_data->envp);
	ft_free_tab(c_data->envp_export);
	free_job_lst(job);
	clear_history();
}
