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


	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(limiter, new_fd, job);
	waitpid(pid, &wstatus, 0);

	if (WIFEXITED(wstatus))
		c_data->exit_status = WEXITSTATUS(wstatus);
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (1);
	return (0);
}

void	heredoc(char *limiter, int *fd, t_job *job)
{
	char	*line;


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
//	free_exit(job);
	exit(EXIT_SUCCESS);
}