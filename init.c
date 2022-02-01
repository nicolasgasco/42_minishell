#include "minishell.h"

void	ft_init_common_data(c_data	*c_data, char **envp)
{
	c_data->envp = envp;
	c_data->username = getenv("USER");
	if (!c_data->username)
		c_data->username = "username";
	c_data->hostname = getenv("HOSTNAME");
	if (!c_data->hostname)
		c_data->hostname = "os";
	c_data->prompt_text = ft_create_prompt_text(c_data->username, c_data->hostname);
	c_data->prompt_newline_text = "> ";
}

char	*ft_create_prompt_text(char	*username, char *hostname)
{
	int		i;
	int		len1;
	int		len2;
	char	*result;
	
	i = 0;
	len1 = ft_strlen(username);
	len2 = ft_strlen(hostname);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 4));
	while (i < len1)
	{
		result[i] = username[i];
		i++;
	}
	result[i] = '@';
	i++;
	while (i < (len1 + len2 + 1))
	{
		result[i] = hostname[i - len1 - 1];
		i++;
	}
	result[i] = ':';
	result[i + 1] = ' ';
	result[i + 2] = '\0';
	return (result);
}
