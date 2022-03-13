#include "minishell.h"

// Structure with global data
void	ft_init_general_data(c_data	*c_data, char **envp)
{
	memset(c_data, 0, sizeof(*c_data));
	init_envp(envp, c_data);
	ft_init_prompt_data(c_data);
	init_export(c_data);
	ft_output_epic_welcome(c_data);
	// ft_init_quotes_data(c_data);
	// ft_init_prompt_data(c_data);
	// ft_init_line_data(c_data);
}

// Function to init envp
void	init_envp(char **envp, c_data *c_data)
{
	int	i;
	i = 0;
	while(envp[i])
		i++;
	c_data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while(envp[++i])
		c_data->envp[i] = ft_strdup(envp[i]);
	c_data->envp[i] = NULL;
}

void	init_export(c_data *c_data)
{
	int	i;
	char	*string;

	i = 0;
	while (c_data->envp[i])
		i++;
	c_data->envp_export = malloc(sizeof(char *) * (i));
	i = 0;
	if(c_data->envp[i])
	{
		while (c_data->envp[i + 1])
		{
			string = ms_make_string(c_data->envp[i]);
			c_data->envp_export[i] = ft_strdup(string);
			free(string);
			i++;
		}
	}
	c_data->envp_export[i] = NULL;
}

void	ft_init_structures(c_data *c_data)
{
	c_data->syntax_error = 0;
	c_data->tokens_list = NULL;
	ft_init_quotes_data(c_data);
}

// Structure containing information on quotes
void	ft_init_quotes_data(c_data *c_data)
{
	c_data->q_data = (q_data *)malloc(sizeof(q_data));
	memset(c_data->q_data, 0, sizeof(q_data));
}

/* Initializing structure containing information on prompt */
void	ft_init_prompt_data(c_data *c_data)
{
	c_data->p_data = (p_data *)malloc(sizeof(p_data));
	memset(c_data->p_data, 0, sizeof(p_data));
	c_data->p_data->username = getenv("USER");
	if (!c_data->p_data->username)
		c_data->p_data->username = ft_strdup("username");
	c_data->p_data->hostname = getenv("HOSTNAME");
	if (!c_data->p_data->hostname)
		c_data->p_data->hostname = ft_strdup("os");
	c_data->p_data->prompt_text = ft_create_prompt_text(c_data->p_data->username, c_data->p_data->hostname);
	c_data->p_data->prompt_nl_text = ft_strdup("> ");
}
