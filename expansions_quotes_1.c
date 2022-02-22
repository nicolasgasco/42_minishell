#include "minishell.h"

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
	}
	else if (quote == '\"')
	{
		if (q_data->s_open == 0)
			q_data->d_open = 1;
		if (q_data->start < i && q_data->s_open == 0)
			ft_add_node_quotes(q_data, i, '\0');
		else if (q_data->start < i && q_data->s_open == 1)
			ft_add_node_quotes(q_data, i, '\'');
		q_data->start = i;
	}
}


