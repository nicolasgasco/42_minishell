/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:51:38 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/05 12:59:36 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path_env(t_cdata *c_data)
{
	int	i;

	i = 0;
	while (c_data->envp[i] && ft_strnstr(c_data->envp[i], "PATH", 4) == 0)
		i++;
	return (i);
}

char	*find_path(char *cmd, t_job *job, t_cdata *c_data)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = find_path_env(c_data);
	if (c_data->envp[i] == NULL)
		error(cmd, 1, job);
	paths = ft_splitc(c_data->envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		if (path)
			free(path);
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(path, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
	}
	free(path);
	ft_free_tab(paths);
	return (NULL);
}

void	error(char *arg, int i, t_job *job)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", arg);
	else if (i == 2)
	{
		printf("minishell: %s: is a directory\n", arg);
		free_job_lst(job);
		exit(126);
	}
	free_job_lst(job);
	exit (127);
}

void	execute(char **cmd, t_job *job, t_cdata *c_data)
{
	char	*path;

	execve(cmd[0], cmd, c_data->envp);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (access(cmd[0], F_OK) == 0)
			error(cmd[0], 2, job);
		error(cmd[0], 1, job);
	}
	path = find_path(cmd[0], job, c_data);
	if (path && (execve(path, cmd, c_data->envp) == -1))
		error(cmd[0], 0, job);
	error(cmd[0], 0, job);
}

void	free_fd(t_job *first)
{
	while (first)
	{
		close(first->fd[0]);
		close(first->fd[1]);
		first = first->next;
	}
}
