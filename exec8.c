/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:13:53 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 12:13:12 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_stat(int g_ex_status)
{
	if (g_ex_status == 131)
		write(1, "Quit: 3\n", 8);
	if (g_ex_status == 130)
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
				g_ex_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_ex_status = 128 + WTERMSIG(status);
				ex_stat(g_ex_status);
			}
			first = first->next;
		}
	}
}

void	ft_put_error(char *str1, char *str2, char *str3, int fd)
{
	ft_putendl_fd(str1, fd);
	ft_putendl_fd(str2, fd);
	ft_putendl_fd(str3, fd);
}
