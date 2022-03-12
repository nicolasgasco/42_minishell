#include "minishell.h"

// User input is tokenized according to quotes to see if they're unclosed or not
void	ft_expand_quotes(c_data *c_data)
{
	ft_tokenize_quotes(c_data->q_data);
	printf("\033[0;34m");
	printf("Quotes linked list");
	printf("\033[0m");
	printf(":\n");
	ft_print_quotes_list(c_data->q_data->quotes_list);
	if (c_data->q_data->d_open || c_data->q_data->s_open)
		c_data->syntax_error = 1;
}


// 1/2 Raw input is parsed and tokenized in a linked list according to quotes
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
		ft_add_node_quotes(q_data, i, '\0');
	else if (q_data->start == 0 || q_data->start != i)
		ft_add_node_quotes(q_data, i, '\0');
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