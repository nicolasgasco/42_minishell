#include "minishell.h"

// All the global variables required by the program
void	ft_init_common_data(c_data	*c_data, char **envp)
{
	memset(c_data, 0, sizeof(*c_data));
	c_data->envp = envp;
	c_data->username = getenv("USER");
	if (!c_data->username)
		c_data->username = "username";
	c_data->hostname = getenv("HOSTNAME");
	if (!c_data->hostname)
		c_data->hostname = "os";
	c_data->prompt_text = ft_create_prompt_text(c_data->username, c_data->hostname);
	c_data->prompt_newline_text = "> ";
	ft_init_quotes_data(c_data);
}

void	ft_init_quotes_data(c_data *c_data)
{
	c_data->q_data = malloc(sizeof(q_data));
	memset(c_data->q_data, 0, sizeof(q_data));
	c_data->q_data->quotes_list = malloc(sizeof(q_data));
	memset(c_data->q_data->quotes_list, 0, sizeof(struct s_node));
	c_data->q_data->quotes_list->next = malloc(sizeof(struct s_node));
	c_data->q_data->quotes_list->length = 0;
	c_data->q_data->quotes_list->quoted = 0;
	c_data->q_data->quotes_list->str = ft_strdup("");
	c_data->q_data->quotes_list->next = NULL;
}

// The text shown when prompting user for input, e.g. username@hostname
char	*ft_create_prompt_text(char	*username, char *hostname)
{
	int		i;
	int		len1;
	int		len2;
	char	*result;
	
	i = 0;
	len1 = ft_strlen(username);
	len2 = ft_strlen(hostname);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 4));
	while (i < len1)
	{
		result[i] = username[i];
		i++;
	}
	result[i] = '@';
	i++;
	while (i < (len1 + len2 + 1))
	{
		result[i] = hostname[i - len1 - 1];
		i++;
	}
	result[i] = ':';
	result[i + 1] = ' ';
	result[i + 2] = '\0';
	return (result);
}

// Initializing first node of list as empty
void	ft_init_quotes_list(q_data *q_data)
{
	q_data->quotes_list->length = 0;
	q_data->quotes_list->quoted = 0;
	q_data->quotes_list->str = ft_strdup("");
	q_data->quotes_list->next = NULL;
}