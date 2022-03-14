/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_quotes_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:57:01 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:57:12 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 2a Logic for substrings that are not preceded by an opening quote */
void	ft_tokenization_logic_unopened(q_data *q_data, int i, char quote)
{
	if (quote == '\'')
	{
		if (q_data->start < i)
		{
			if (q_data->d_open == 1)
				ft_add_node_quotes(q_data, i, '\0');
			else if (q_data->d_open == 0)
			{
				q_data->s_open = 1;
				ft_add_node_quotes(q_data, i, '\0');
			}
		}
	}
	else if (quote == '\"')
	{
		if (q_data->s_open == 0)
			q_data->d_open = 1;
		if (q_data->start < i)
		{
			if (q_data->s_open == 0)
				ft_add_node_quotes(q_data, i, '\0');
			else if (q_data->s_open == 1)
				ft_add_node_quotes(q_data, i, '\'');
		}
	}
	q_data->start = i;
}

/* 2b Logic for substrings that are preceded by an opening quote */
void	ft_tokenization_logic_open(q_data *q_data, int i, char quote)
{
	if (quote == '\'')
	{
		q_data->s_open = 0;
		if (q_data->start < i)
			ft_add_node_quotes(q_data, i, quote);
	}
	else if (quote == '\"')
	{
		q_data->d_open = 0;
		if (q_data->start < i)
			ft_add_node_quotes(q_data, i, quote);
	}
	q_data->start = i + 1;
}

/* Add a new node to the linked list containing the tokenized raw input */
void	ft_add_node_quotes(q_data *q_data, int end, char quote)
{
	struct q_node	*new_node;
	struct q_node	*curr;
	int				i;

	curr = q_data->quotes_list;
	new_node = (struct q_node *)malloc(sizeof(struct q_node));
	if (new_node == NULL)
		exit(1);
	new_node->str = ft_write_str_to_node(q_data, end);
	new_node->length = end - q_data->start;
	new_node->q_type = quote;
	new_node->next = NULL;
	i = 0;
	while (curr && curr->next != NULL)
	{
		curr = curr->next;
		i++;
	}
	if (curr)
		curr->next = new_node;
	else
		q_data->quotes_list = new_node;
}

/* Three cases: quoted string, quoted string but empty, unquoted string */
char	*ft_write_str_to_node(q_data *q_data, int end)
{
	if (end - q_data->start > 1)
		return (ft_create_quoted_token(q_data->raw_input, q_data->start, end - q_data->start));
	else
	{
		if (q_data->raw_input[q_data->start] == '\'' || q_data->raw_input[q_data->start] == '\"')
			return ((ft_create_quoted_token_empty(q_data->raw_input, q_data->start)));
		else
			return (ft_create_unquoted_token(q_data->raw_input, q_data->start, end - q_data->start));
	}
}
