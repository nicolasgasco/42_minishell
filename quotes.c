#include "minishell.h"

void ft_tokenize_quotes(c_data *c_data)
{
	int		i;
	int		start;
	int		quotes_open;
	char	*line;
	
	line = c_data->raw_input;
	start = 0;
	quotes_open = 0;
	if (line[0] == '\'')
		quotes_open = 1;
	i = 1;
	while (line[i] != '\0')
	{
		if (quotes_open == 0)
		{
			if (line[i] == '\'' && line[i - 1] != '\\')
				ft_tokenize_quotes_util_0(c_data, &i, &start, &quotes_open);
		}
		else if (quotes_open == 1)
		{
			if (line[i] == '\'')
				ft_tokenize_quotes_util_1(c_data, &i, &start, &quotes_open);
		}
		i++;
	}
	if (c_data->quotes_list->next == NULL)
		ft_add_node_quotes(c_data, start, i, 0);
}

void	ft_tokenize_quotes_util_0(c_data *c_data, int *i, int *start, int *quotes_open)
{
	*quotes_open = 1;
	if (*start < *i)
		ft_add_node_quotes(c_data, *start, *i, 0);
	*start = *i;
}

void	ft_tokenize_quotes_util_1(c_data *c_data, int *i, int *start, int *quotes_open)
{
	*quotes_open = 0;
	if (*start < *i)
		ft_add_node_quotes(c_data, *start, *i + 1, 1);
	*start = *i + 1;
}

void	ft_add_node_quotes(c_data *c_data, int start, int end, int quoted)
{
	struct s_node	*new_node;
	struct s_node	*curr;

	curr = c_data->quotes_list;
	new_node = malloc(sizeof(struct s_node));
	if (new_node == NULL)
		exit(1);
	new_node->str = ft_substr(c_data->raw_input, start, end - start);
	printf("Str in node: ->%s<-\n", new_node->str);
	new_node->length = end - start;
	new_node->quoted = quoted;
	while (curr->next != NULL)
		curr = curr->next;
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

