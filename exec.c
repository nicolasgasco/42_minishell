/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:48:45 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/10 16:28:19 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_to_tab(struct s_tnode *token, t_job *job)
{
	int	i;
	int	counter;

	if (!job->cmd)
	{
		counter = counter_string(token);
		job->cmd = ft_calloc(counter + 1, sizeof(char *));
	}
	i = 0;
	while (job->cmd[i])
		i++;
	job->cmd[i] = ft_calloc((ft_strlen(token->str) + 1), sizeof(char));
	ft_strcpy(job->cmd[i], token->str);
}

void	ms_job_addback(t_job **job, t_job *new_job)
{
	t_job	*last_job;

	if (*job == NULL)
		*job = new_job;
	else
	{
		last_job = ms_job_last(*job);
		last_job->next = new_job;
		new_job->previous = last_job;
	}
}

void	free_token_lst(struct s_tnode *tok)
{
	struct s_tnode	*temp;

	temp = NULL;
	while (tok)
	{
		temp = tok->next;
		free(tok->str);
		free(tok);
		tok = temp;
	}
	free(tok);
}

t_job	*ms_job_newlst(void)
{
	t_job	*new;

	new = ft_calloc(1, sizeof(t_job));
	if (!new)
		return (NULL);
	return (new);
}

t_job	*ft_create_exec(t_job *job, struct s_tnode *token)
{
	job = ms_job_newlst();
	while (token && token->str)
	{
		if (token->type == PIPE)
		{
			ms_job_addback(&job, ms_job_newlst());
			job = job->next;
		}
		else if (token->type == STRING)
			token_to_tab(token, job);
		else if (is_redirection(token))
		{
			job = redirection_to_tab(token, job);
			token = token->next;
		}
		token = token->next;
	}
	free_token_lst(ms_head_list(token));
	return (ms_head_list_job(job));
}			
