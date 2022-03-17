#include "minishell.h"

int	built_envp(t_cdata *t_cdata)
{
	int	i;

	i = 0;
	while(t_cdata->envp[i])
		printf("%s\n", t_cdata->envp[i++]);
	return(0);
}
