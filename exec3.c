/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-cor <adel-cor@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:26:44 by adel-cor          #+#    #+#             */
/*   Updated: 2022/04/05 12:30:54 by adel-cor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_heredocs(t_job *job, t_cdata *c_data)
{
	while (job)
	{
		if (check_heredoc(job->file, job->fd[0], job, c_data) == 1)
			return (1);
		job = job->next;
	}
	return (0);
}

int	check_heredoc(char **redir, int stdin_fd, t_job *job, t_cdata *c_data)
{
	int	i;

	i = 0;
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
		{
			if (redir_heredoc(redir[i + 1], stdin_fd, job, c_data) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	redir_heredoc(char *limiter, int fd, t_job *job, t_cdata *c_data)
{
	int		new_fd[2];
	pid_t	pid;
	int		wstatus;
//	signal
	pipe(new_fd);
	// sig_data.is_child = 1;
	pid = fork();
	if (pid == 0)
	{
		fprintf(output, "Inside %d\n", getpid());
		fflush(output);
		ft_shortcut_events_interactive();
		heredoc(limiter, new_fd, job, c_data);
	}
	else
		ft_ignore_all_signals();
	waitpid(pid, &wstatus, 0);
	// sig_data.is_child = 0;
//	signal
	if (WIFEXITED(wstatus))
		c_data->exit_status = WEXITSTATUS(wstatus);
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (1);
	return (0);
}

void	heredoc(char *limiter, int *fd, t_job *job, t_cdata *c_data)
{
	char	*line;
//	signal
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	free_ex(job, c_data);
	exit(EXIT_SUCCESS);
}
