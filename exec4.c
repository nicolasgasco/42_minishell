/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:31:24 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 10:25:13 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*ms_head_list_job(t_job *job)
{
	while (job)
	{
		if (!job->previous)
			return (job);
		job = job->previous;
	}
	return (job);
}

struct	s_tnode	*ms_head_list(struct s_tnode *token)
{
	while (token)
	{
		if (!token->prev)
			return (token);
		token = token->prev;
	}
	return (token);
}

t_job	*ms_job_last(t_job *job)
{
	while (job)
	{
		if (job->next == NULL)
			return (job);
		job = job->next;
	}
	return (job);
}

int	redir_counter(struct s_tnode *tok)
{
	int	i;

	i = 0;
	while (tok && tok->next)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		if (tok->type == STRING)
			tok = tok->next;
		if (is_redirection(tok))
			i++;
		tok = tok->next;
	}
	return (i);
}

t_job	*redirection_to_tab(struct s_tnode *token, t_job *job)
{
	int	counter;
	int	i;

	if (!job->file)
	{
		counter = redir_counter(token);
		job->file = ft_calloc((counter * 2) + 1, sizeof(char *));
	}
	i = 0;
	while (job->file[i])
		i++;
	job->file[i] = ft_calloc(ft_strlen(token->str) + 1, sizeof(char));
	ft_strcpy(job->file[i], token->str);
	i++;
	if (!token->next)
		return (job);
	token = token->next;
	job->file[i] = ft_calloc(ft_strlen(token->str) + 1, sizeof(char));
	ft_strcpy(job->file[i], token->str);
	return (job);
}
