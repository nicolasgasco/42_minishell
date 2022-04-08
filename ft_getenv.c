#include "minishell.h"

char	*ft_get_env(char *var_name, char **env)
{
	int		i;
	char	*temp;
	char	*temp2;
	
	temp = ft_strjoin(var_name, "=");
	// printf("temp: %s\n", temp);
	temp2 = NULL;
	i = 0;
	while(env[i])
	{
		if(!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			// printf("llego\n");
			temp2 = ft_substr(env[i], ft_strlen(temp), ((ft_strlen(env[i]) - ft_strlen(temp))));
			free(temp);
			return (temp2);
		}
		i++;
	}
	free(temp);
	return(temp2);
}


