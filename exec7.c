/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:59:57 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/12 12:12:35 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_job_lst(t_job *job)
{
	t_job	*temp;

	temp = NULL;
	while (job)
	{
		temp = job->next;
		if (job->cmd)
			ft_free_tab(job->cmd);
		if (job->file)
			ft_free_tab(job->file);
		free(job);
		job = temp;
	}
}

int	open_file(char *argv, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		if (access(argv, F_OK) == 0)
			ft_put_error("minishell: ", argv, ": Is a directory\n", 2);
		else
			ft_put_error("minishell: ", argv,
				": No such file or directory\n", 2);
		if (quit == 0)
			exit(1);
	}
	return (file);
}

int	check_redirection(t_job *job, int quit)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	while (job->file && job->file[i])
	{
		if (ft_strcmp(job->file[i], "<") == 0)
			fd[0] = open_file(job->file[++i], 2, quit);
		else if (ft_strcmp(job->file[i], ">") == 0)
			fd[1] = open_file(job->file[++i], 1, quit);
		else if (ft_strcmp(job->file[i], ">>") == 0)
			fd[1] = open_file(job->file[++i], 0, quit);
		else if (ft_strcmp(job->file[i], "<<") == 0)
			dup2(job->fd[0], STDIN_FILENO);
		i++;
	}
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
	return (0);
}

int	check_builtins(char **arg)
{
	if (ft_strcmp(arg[0], "echo") == 0
		||ft_strcmp(arg[0], "cd") == 0
		||ft_strcmp(arg[0], "pwd") == 0
		||ft_strcmp(arg[0], "export") == 0
		||ft_strcmp(arg[0], "unset") == 0
		||ft_strcmp(arg[0], "env") == 0
		||ft_strcmp(arg[0], "exit") == 0)
		return (0);
	else
		return (1);
}

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, 0);
	close(saved_stdin);
	dup2(saved_stdout, 1);
	close(saved_stdout);
}
