#include "minishell.h"

// 1/2 Raw input is parsed and tokenized in a linked list according to quotes. First empty linked node is pruned at the end of function
void ft_tokenize_quotes(q_data *q_data)
{
	int i;

	if (q_data->raw_input[0] == '\'')
		q_data->s_open = 1;
	else if (q_data->raw_input[0] == '\"')
		q_data->d_open = 1;
	i = 1;
	while (q_data->raw_input[i] != '\0')
	{
		if (q_data->raw_input[i] == '\'' && q_data->d_open == 0)
			ft_tokenization_logic(q_data, q_data->raw_input, i, '\'');
		else if (q_data->raw_input[i] == '\"' && q_data->s_open == 0)
			ft_tokenization_logic(q_data, q_data->raw_input, i, '\"');
		i++;
	}
	if (q_data->d_open || q_data->s_open)
	{
		if (q_data->raw_input[i + 1] != '\0')
			ft_add_node_quotes(q_data, i, '\0');
	}
	else if (q_data->start == 0 || q_data->start != i)
		ft_add_node_quotes(q_data, i, '\0');
	ft_prune_starting_node(&q_data->quotes_list);
}

// 2/2 For both types of quotes, different tokenization logics are applied
void ft_tokenization_logic(q_data *q_data, char *line, int i, char quote)
{
	if (quote == '\'')
	{
		if (q_data->s_open == 0)
		{
			if (line[i - 1] != '\\')
			{
				ft_tokenization_logic_closed(q_data, i, quote);
				q_data->s_open = 1;
			}
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
		{
			if (line[i - 1] != '\\')
				ft_tokenization_logic_open(q_data, i, quote);	
		}
	}
}

// 2b Logic for substrings that are preceded by an opening quote
void ft_tokenization_logic_open(q_data *q_data, int i, char quote)
{
	if (quote == '\'')
	{
		q_data->s_open = 0;
		if (q_data->start < i)
			ft_add_node_quotes(q_data, i, quote);
		q_data->start = i + 1;
	}
	else if (quote == '\"')
	{
		q_data->d_open = 0;
		if (q_data->start < i)
		ft_add_node_quotes(q_data, i, quote);
		q_data->start = i + 1;
	}
}

// 2a Logic for substrings that are not preceded by an opening quote
void ft_tokenization_logic_closed(q_data *q_data, int i, char quote)
{
	if (quote == '\'')
	{
		if (q_data->start < i && q_data->d_open == 1)
			ft_add_node_quotes(q_data, i, '\0');
		else if (q_data->start < i && q_data->d_open == 0)
		{
			q_data->s_open = 1;
			ft_add_node_quotes(q_data, i, '\0');
		}
		q_data->start = i;
	}
	else if (quote == '\"')
	{
		if (q_data->s_open == 0)
			q_data->d_open = 1;
		if (q_data->start < i && q_data->s_open == 0)
			ft_add_node_quotes(q_data, i, '\0');
		else if (q_data->s_open < i && q_data->s_open == 1)
			ft_add_node_quotes(q_data, i, '\'');
		q_data->start = i;
	}
}


