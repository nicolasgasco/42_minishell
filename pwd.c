#include "minishell.h"

int	built_pwd(void)
{
	char	str[PATH_MAX];

	if(getcwd(str, sizeof(str)) == NULL)
		return(1);
	printf("%s\n", str);
	return(0);
}
