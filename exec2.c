/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:00:49 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 12:07:13 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtins(char **arg, int i, t_job *job, t_cdata *c_data)
{
	if (arg)
	{
		if (ft_strcmp(arg[0], "echo") == 0)
			g_ex_status = built_echo(arg);
		else if (ft_strcmp(arg[0], "cd") == 0)
			g_ex_status = built_cd(arg[1], c_data);
		else if (ft_strcmp(arg[0], "pwd") == 0)
			g_ex_status = built_pwd();
		else if (ft_strcmp(arg[0], "export") == 0)
			g_ex_status = built_export(arg + 1, c_data);
		else if (ft_strcmp(arg[0], "unset") == 0)
			g_ex_status = built_unset(arg + 1, c_data);
		else if (ft_strcmp(arg[0], "env") == 0)
			g_ex_status = built_envp(c_data);
		else if (ft_strcmp(arg[0], "exit") == 0)
			built_exit(arg + 1);
		else
			return (1);
	}
	if (i == 0)
		return (0);
	free_job_lst(job);
	exit(0);
}

int	ms_exec_builtins(t_job *job, t_cdata *c_data)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	if (job && job->next == NULL)
	{
		if (job->cmd && check_builtins(job->cmd) == 1)
			return (0);
		if (check_redirection(job, 1) == 1)
			return (1);
		if (ms_builtins(job->cmd, 0, job, c_data) == 0)
		{
			restore_fd(saved_stdin, saved_stdout);
			return (1);
		}
	}
	return (0);
}

void	init_pipe(t_job *job)
{
	while (job)
	{
		pipe(job->fd);
		job = job->next;
	}
}

void	child_process(t_job *job, t_job *first, t_cdata *c_data)
{
	job->pid = fork();
	if (job->pid == -1)
		ft_putendl_fdnl("Dang! This fork didn't work!", 2);
	if (job->pid == 0)
	{
		ft_shortcut_events_interactive();
		if (job->previous != NULL)
			dup2(job->previous->fd[0], STDIN_FILENO);
		if (job->next != NULL)
			dup2(job->fd[1], STDOUT_FILENO);
		check_redirection(job, 0);
		close(job->fd[0]);
		close(job->fd[1]);
		free_fd(first);
		if (job->cmd && ms_builtins(job->cmd, 1, first, c_data) == 1)
			execute(job->cmd, first, c_data);
	}
	else
		ft_ignore_all_signals();
	if (job->previous != NULL)
		close(job->previous->fd[0]);
	close(job->fd[1]);
}

void	executor(t_job *job, t_cdata *c_data)
{
	t_job	*first;

	first = job;
	init_pipe(first);
	if (make_heredocs(job, c_data) == 1 || ms_exec_builtins(job, c_data) == 1)
		return ;
	if (job && job->cmd)
	{
		mini_exec(job, first, c_data);
	}
}
