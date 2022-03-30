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
//		free_exit(job);
		free_job_lst(job);
		exit(126);
	}
//	free_exit(job);
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
	while(first)
	{
		close(first->fd[0]);
		close(first->fd[1]);
		first = first->next;
	}
}

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
			printf("minishell: %s Is a directory\n", argv);
		else
			printf("minishell: no such file or directory: %s\n", argv);
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

int	ms_builtins(char **arg, int i, t_job *job, t_cdata *c_data)
{
	if (arg)
	{
		if (ft_strcmp(arg[0], "echo") == 0)
			c_data->exit_status = built_echo(arg);
		else if (ft_strcmp(arg[0], "cd") == 0)
			c_data->exit_status = built_cd(arg[1], c_data);
		else if (ft_strcmp(arg[0], "pwd") == 0)
			c_data->exit_status = built_pwd();
		else if (ft_strcmp(arg[0], "export") == 0)
			c_data->exit_status = built_export(arg + 1, c_data);
		else if (ft_strcmp(arg[0], "unset") == 0)
			c_data->exit_status = built_unset(arg + 1, c_data);
		else if (ft_strcmp(arg[0], "env") == 0)
			c_data->exit_status = built_envp(c_data);
//		else if (ft_strcmp(arg[0], "exit") == 0)
//			ms_exit(arg + 1, job);
		else
			return (1);
	}
	if (i == 0)
		return (0);
//	free_exit(job);
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
		printf("Dang! This fork didn't work!");
	if (job->pid == 0)
	{
	
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
	if (job->previous != NULL)
		close(job->previous->fd[0]);
	close(job->fd[1]);
}
void	executor(t_job *job, t_cdata *c_data)
{
	t_job	*first;
	int		status;

	first = job;
	init_pipe(first);
	if (ms_exec_builtins(job, c_data) == 1)
		return ;
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
				c_data->exit_status = WEXITSTATUS(status);
			first = first->next;
		}
	}
	
}
