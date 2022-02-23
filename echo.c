#include "minishell.h"

int check_new_line(char *str)
{
	int i;

	i = 0;
	if(str && str[i])
	{
		if(str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == '\0')
			return(0);
	}
	return(1);
}


int	built_echo(char **arg)
{
	int	x;
	int	i;

	x = 1;
	i = 0;
	
	if (!check_new_line(arg[1]))
	{
		x = 2;
		i = 1;
	}

	while(arg[x])
	{
		printf("%s", arg[x]);
		if (arg[x + 1] != NULL)
			printf(" ");
		x++;
	}
	if(!i)
		printf("\n");
	
	return(0);
}
