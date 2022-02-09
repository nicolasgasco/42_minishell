#include "minishell.h"

// Main loop, input is saved and tokenized
void	ft_start_loop(c_data *c_data)
{
	char	*line_read;

	while (1)
	{
		line_read = (char *)NULL;
		line_read = rl_gets(line_read, c_data->prompt_text);
		if (ft_are_quotes_unclosed(line_read))
		{
			while (1)
			{
				line_read = rl_gets(line_read, c_data->prompt_newline_text);
				if (!ft_are_quotes_unclosed(line_read))
					break;
			}
		}
		line_read = ft_expand_line(line_read);
		c_data->tokens = ft_tokenize(line_read, c_data);
		printf("%s\n", line_read);
		// c_data->paths = ft_splitc(getenv("PATH"), ':');
		ft_check_cmd(c_data->cmd);
	}
}

// Program doesn't accept arguments
int	main(int argc, char *argv[], char *envp[])
{
	c_data c_data;

	if (argc != 1 || argv[1])
	{
		printf("Error: arguments\n");
		return (1);
	}
	ft_init_common_data(&c_data, envp);
	ft_start_loop(&c_data);
	return (0);
}