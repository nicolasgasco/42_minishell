#include "minishell.h"

void	built_pwd(void)
{
	char	str[PATH_MAX];

	if(getcwd(str, sizeof(str)) == NULL)
		return ;
	printf("%s\n", str);
	return ;
}
