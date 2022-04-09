#include "../minishell.h"

int	ft_isalldigit(char *str)
{
	int	i;
	i = 0;
	printf("str es %s\n", str);
	while(str)
	{
		if(str[i] >= '0' && str[i] <= '9')
			return(1);
		i++;
	}
	return(0);
}
