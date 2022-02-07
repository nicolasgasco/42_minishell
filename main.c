#include "minishell.h"



// Main loop, input is saved and tokenized
void	ft_start_loop(c_data *c_data)
{
	int			i;
	static char	*line_read;

	i = 0;
	while (1)
	{
		line_read = rl_gets(line_read, c_data->prompt_text);
		if(*line_read)
		{
		c_data->tokens = ft_tokenize(line_read, c_data);
		c_data->paths = ft_splitc(getenv("PATH"), ':');
		ft_check_cmd(c_data);
		}
		i++;
		
	}
}

// Program doesn't accept arguments
int	main(int argc, char *argv[], char *envp[])
{
	c_data	c_data;
		
	if (argc != 1 || argv[1])
	{
		printf("Error: arguments\n");
		return (1);
	}
	ft_init_common_data(&c_data, envp);
	ft_start_loop(&c_data);
	return (0);
}
