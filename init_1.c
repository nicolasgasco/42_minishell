#include "minishell.h"

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
