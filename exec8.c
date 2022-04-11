/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:13:53 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/11 12:21:01 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_stat(t_cdata *c_data, int status)
{
	if (c_data->exit_status == 131)
		write(1, "Quit: 3\n", 8);
	if (c_data->exit_status == 130)
		write(1, "\n", 1);
}

void	mini_exec(t_job *job, t_job *first, t_cdata *c_data)
{
	int	status;

	if (job && job->cmd)
	{
		while (job)
		{
			child_process(job, first, c_data);
			job = job->next;
			first = ms_head_list_job(first);
		}
		while (first)
		{
			waitpid(first->pid, &status, 0);
			if (WIFEXITED(status))
			{
				c_data->exit_status = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				c_data->exit_status = 128 + WTERMSIG(status);
				ex_stat(c_data, status);
			}
			first = first->next;
		}
	}
}
