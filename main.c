#include "minishell.h"

void	ft_start_loop(c_data *c_data)
{
	int			i;
	static char	*line_read;

	i = 0;
	while (1)
	{
		line_read = rl_gets(line_read, c_data->prompt_text);
		c_data->tokens = ft_tokenize(line_read, c_data);
		ft_print_array(c_data->tokens);
		ft_check_cmd(c_data->cmd);
		i++;
	}
}

int	main(void)
{
	c_data	c_data;
		
	ft_init_common_data(&c_data);
	ft_start_loop(&c_data);
	return (0);
}