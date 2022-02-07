#include "minishell.h"

void	built_envp(c_data *c_data)
{
	int	i;

	i = 0;
	while(c_data->envp[i])
		printf("%s\n", c_data->envp[i++]);
	return ;
}
