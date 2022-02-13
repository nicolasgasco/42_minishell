#include "minishell.h"

// Function to init envp

void	init_envp(char **envp, c_data	*c_data)
{
	int	i;
	i = 0;
	while(envp[i])
		i++;
	c_data->envp = malloc(sizeof(char *) * (i + 1));
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
	c_data->env_export[i] = NULL;
}
// All the global variables required by the program
void	ft_init_common_data(c_data	*c_data, char **envp)
{
	init_envp(envp, c_data);
	c_data->username = getenv("USER");
	if (!c_data->username)
		c_data->username = "username";
	c_data->hostname = getenv("HOSTNAME");
	if (!c_data->hostname)
		c_data->hostname = "os";
	printf("\n||WAR MACHINE IS READY||\n\n");
	printf("Project Minishell.\n\n");
	printf("Made with love by NICO GASCO & TONI DEL CORRAL.\n\n");
	printf("Welcome %s, you are now in charge. Good Luck.\n\n", c_data->username);
	c_data->prompt_text = ft_create_prompt_text(c_data->username, c_data->hostname);
}

// The text shown when prompting user for input, e.g. username@hostname
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
