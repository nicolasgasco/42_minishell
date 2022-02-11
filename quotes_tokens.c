#include "minishell.h"

void ft_tokenize_quotes(c_data *c_data)
{
	int i;
	q_data *q_data;
	char *line;

	line = c_data->q_data->raw_input;
	q_data = c_data->q_data;
	if (line[0] == '\'')
		q_data->s_open = 1;
	else if (line[0] == '\"')
		q_data->d_open = 1;
	i = 1;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			ft_tokenization_logic(q_data, line, i, '\'');
		else if (line[i] == '\"')
			ft_tokenization_logic(q_data, line, i, '\"');
		i++;
	}
	if (line[i - 1] != '\'' && line[i - 1] != '\"')
		ft_add_node_quotes(q_data, i, 0, '\0');
}

void ft_tokenization_logic(q_data *q_data, char *line, int i, char quote)
{
	if (quote == '\'')
	{
		if (q_data->s_open == 0)
		{
			if (line[i - 1] != '\\')
				ft_tokenization_logic_closed(q_data, i, quote);
		}
		else if (q_data->s_open == 1)
			ft_tokenization_logic_open(q_data, i, quote);
	}
	else if (quote == '\"')
	{
		if (q_data->d_open == 0)
		{
			if (line[i - 1] != '\\')
				ft_tokenization_logic_closed(q_data, i, quote);
		}
		else if (q_data->d_open == 1)
			ft_tokenization_logic_open(q_data, i, quote);	
	}
}

void ft_tokenization_logic_closed(q_data *q_data, int i, char quote)
{
	if (quote == '\'')
	{
		if (q_data->start < i && q_data->d_open == 1)
			ft_add_node_quotes(q_data, i, 0, '\"');
		else if (q_data->start < i && q_data->d_open == 0)
		{
			q_data->s_open = 1;
			ft_add_node_quotes(q_data, i, 0, '\'');
		}
		q_data->start = i;
	}
	else if (quote == '\"')
	{
		if (q_data->s_open == 0)
			q_data->d_open = 1;
		if (q_data->start < i && q_data->s_open == 0)
			ft_add_node_quotes(q_data, i, 0, '\0');
		else if (q_data->s_open < i && q_data->s_open == 1)
			ft_add_node_quotes(q_data, i, 0, '\'');
		q_data->start = i;
	}
}

void ft_tokenization_logic_open(q_data *q_data, int i, char quote)
{
	if (quote == '\'')
	{
		q_data->s_open = 0;
		if (q_data->start < i)
			ft_add_node_quotes(q_data, i + 1, 1, quote);
		q_data->start = i + 1;
	}
	else if (quote == '\"')
	{
		q_data->d_open = 0;
		if (q_data->start < i)
		ft_add_node_quotes(q_data, i + 1, 1, quote);
		q_data->start = i + 1;
	}
}

