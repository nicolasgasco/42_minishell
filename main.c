#include "minishell.h"

void	ft_start_loop(c_data *c_data)
{
	static char	*line_read;

	c_data->username = readline("Enter user name: ");
	printf("Hi, %s. Welcome!\n", c_data->username);
	while (1)
		line_read = rl_gets(line_read);
}

int	main(void)
{
	c_data	c_data;
		
	ft_init_common_data(&c_data);
	ft_start_loop(&c_data);
	return (0);
}