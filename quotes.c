#include "minishell.h"

void ft_tokenize_quotes(c_data *c_data)
{
	int		i;
	q_data	*q_data;
	char	*line;

	line = c_data->q_data->raw_input;
	q_data = c_data->q_data;
	if (line[0] == '\'')
		q_data->q_open = 1;
	i = 1;
	while (line[i] != '\0')
	{
		if (q_data->q_open == 0)
		{
			if ((line[i] == '\'' || line[i] == '\"') && line[i - 1] != '\\')
				ft_tokenize_quotes_util_0(q_data, &i, line[i]);
		}
		else if (q_data->q_open == 1)
		{
			if (line[i] == '\'' || line[i] == '\"')
				ft_tokenize_quotes_util_1(q_data, &i, line[i]);
		}
		i++;
	}
	if (c_data->q_data->quotes_list->next == NULL)
		ft_add_node_quotes(q_data, i, 0, 0);
}

void	ft_tokenize_quotes_util_0(q_data *q_data, int *i, char quote)
{
	q_data->q_open = 1;
	if (q_data->start < *i)
		ft_add_node_quotes(q_data, *i, 0, quote);
	q_data->start = *i;
}

void	ft_tokenize_quotes_util_1(q_data *q_data, int *i, char quote)
{
	q_data->q_open = 0;
	if (q_data->start < *i)
		ft_add_node_quotes(q_data, *i + 1, 1, quote);
	q_data->start = *i + 1;
}

void	ft_add_node_quotes(q_data *q_data, int end, int quoted, char quote)
{
	struct s_node	*new_node;
	struct s_node	*curr;
	int				i;

	curr = q_data->quotes_list;
	new_node = malloc(sizeof(struct s_node));
	if (new_node == NULL)
		exit(1);
	new_node->str = ft_substr(q_data->raw_input, q_data->start, end - q_data->start);
	new_node->length = end - q_data->start;
	new_node->quoted = quoted;
	new_node->q_type = quote;
	new_node->next = NULL;
	i = 0;
	while (curr->next != NULL)
	{
		curr = curr->next;
		i++;
	}
	printf("||%s||\t\t\t(quotes: %c) in node number %d\n", new_node->str, new_node->q_type, i);
	curr->next = new_node;
}

char    *ft_expand_simple_quotes(char *line)
{
	char    *result;
	int     new_length;
	
	new_length = ft_str_len_unescaped(line, '\'');
	result = malloc(sizeof(char) * (new_length + 1));
	result = ft_expand_escaped_quotes(line, new_length);
	return (result);
}

// Quotes are removed or kept depending if they're escaped inside or outside a set of quotes
char *ft_expand_escaped_quotes(char *line, int length)
{
	int     i;
	int     y;
	int     word_started;
	char    *result;

	ft_expanded_escaped_quotes_init(&i, &y, &word_started);
	result = malloc(sizeof(char) * (length + 1));
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			if (i > 0 && line[i - 1] == '\\')
			{
				if (word_started == 1)
					word_started = 0;
				else
					i--;
			}
			else
				word_started = ft_toggle_word_started(word_started);
			i++;
		}
		if (line[i] == '\\' && word_started == 0)
			i++;
		result[y] = line[i];
		i++;
		y++;
	}
	result[y] = '\0';
	printf("Result: %s\n", result);
	return (result);
}

void    ft_expanded_escaped_quotes_init(int *i, int *y, int *w)
{
	*i = 0;
	*y = 0;
	*w = 0;
}

