#include "minishell.h"

// Structure with global data
void	ft_init_common_data(c_data	*c_data, char **envp)
{
	memset(c_data, 0, sizeof(*c_data));
	c_data->envp = envp;
	// ft_init_quotes_data(c_data);
	// ft_init_prompt_data(c_data);
	// ft_init_line_data(c_data);
}

void	ft_init_structures(c_data *c_data)
{
	c_data->syntax_error = 0;
	ft_init_quotes_data(c_data);
	ft_init_prompt_data(c_data);
	ft_init_line_data(c_data);
}

// Structure containing information on quotes
void	ft_init_quotes_data(c_data *c_data)
{
	c_data->q_data = malloc(sizeof(q_data));
	memset(c_data->q_data, 0, sizeof(q_data));
}

// Structure containing information on prompt
void	ft_init_prompt_data(c_data *c_data)
{
	c_data->p_data = malloc(sizeof(p_data));
	memset(c_data->p_data, 0, sizeof(p_data));
	c_data->p_data->username = getenv("USER");
	if (!c_data->p_data->username)
		c_data->p_data->username = "username";
	c_data->p_data->hostname = getenv("HOSTNAME");
	if (!c_data->p_data->hostname)
		c_data->p_data->hostname = "os";
	c_data->p_data->prompt_text = ft_create_prompt_text(c_data->p_data->username, c_data->p_data->hostname);
	c_data->p_data->prompt_nl_text = "> ";
}

// Structure containing information on user input
void	ft_init_line_data(c_data *c_data)
{
	c_data->l_data = malloc(sizeof(l_data));
	memset(c_data->l_data, 0, sizeof(l_data));
}
