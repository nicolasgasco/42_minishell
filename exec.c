#include "minishell.h"

t_job	*ms_head_list_job(t_job *job)
{
	while(job)
	{
		if(!job->previous)
			return(job);
		job = job->previous;
	}
	return(job);
}


struct s_tnode *ms_head_list(struct s_tnode *token)
{
	while(token)
	{
		if(!token->prev)
			return(token);
		token = token->prev;
	}
	return(token);
}


t_job	*ms_job_last(t_job *job)
{
	while(job)
	{
		if(job->next == NULL)
			return(job);
		job = job->next;
	}
	return(job);
}

int	redir_counter(struct s_tnode *tok)
{
	printf("entra bien en redir\n");
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
	printf("sale de bucle redir\n");
	return (i);
}

t_job	*redirection_to_tab(struct s_tnode *token, t_job *job)
{

	int	counter;
	int	i;

	if (!job->file)
	{	
		printf("no file\n");
		counter = redir_counter(token);
		printf("redir_counter_ok\n");
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

bool	is_redirection(struct s_tnode *token)
{
	if (token->type == REDIR_L || token->type == REDIR_R 
		|| token->type == APPEND)
		return (true);
	return (false);
}

int	counter_string(struct s_tnode *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		else if (tok->type == REDIR_L || tok->type == REDIR_R
			|| tok->type == APPEND)
			tok = tok->next;
		else if (tok->type == STRING)
			i++;
		tok = tok->next;
	}
	return (i);
}
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

t_job *ft_create_exec(t_job *job, struct s_tnode *token)
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
	printf("sale del bucle\n");
	free_token_lst(ms_head_list(token));
	return (ms_head_list_job(job));

}
			
