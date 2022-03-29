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
void	ft_tokenization_logic_unopened(t_qdata *t_qdata, int i, char quote)
{
	if (quote == '\'')
	{
		if (t_qdata->start < i)
		{
			if (t_qdata->d_open == 1)
				ft_add_node_quotes(t_qdata, i, '\0');
			else if (t_qdata->d_open == 0)
			{
				t_qdata->s_open = 1;
				ft_add_node_quotes(t_qdata, i, '\0');
			}
		}
	}
	else if (quote == '\"')
	{
		if (t_qdata->s_open == 0)
			t_qdata->d_open = 1;
		if (t_qdata->start < i)
		{
			if (t_qdata->s_open == 0)
				ft_add_node_quotes(t_qdata, i, '\0');
			else if (t_qdata->s_open == 1)
				ft_add_node_quotes(t_qdata, i, '\'');
		}
	}
	t_qdata->start = i;
}

/* 2b Logic for substrings that are preceded by an opening quote */
void	ft_tokenization_logic_opened(t_qdata *t_qdata, int i, char quote)
{
	if (quote == '\'')
	{
		t_qdata->s_open = 0;
		if (t_qdata->start < i)
			ft_add_node_quotes(t_qdata, i, quote);
	}
	else if (quote == '\"')
	{
		t_qdata->d_open = 0;
		if (t_qdata->start < i)
			ft_add_node_quotes(t_qdata, i, quote);
	}
	t_qdata->start = i + 1;
}

/* Add a new node to the linked list containing the tokenized raw input */
void	ft_add_node_quotes(t_qdata *t_qdata, int end, char quote)
{
	struct s_qnode	*new_node;
	struct s_qnode	*curr;
	int				i;

	curr = t_qdata->quotes_list;
	new_node = (struct s_qnode *)malloc(sizeof(struct s_qnode));
	if (new_node == NULL)
		exit(1);
	new_node->str = ft_write_str_to_node(t_qdata, end);
	new_node->length = end - t_qdata->start;
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
		t_qdata->quotes_list = new_node;
}

/* Three cases: quoted string, quoted string but empty, unquoted string */
char	*ft_write_str_to_node(t_qdata *t_qdata, int end)
{
	if (end - t_qdata->start > 1)
		return (ft_create_quoted_token(t_qdata->raw_input, t_qdata->start, end - t_qdata->start));
	else
	{
		if (t_qdata->raw_input[t_qdata->start] == '\'' || t_qdata->raw_input[t_qdata->start] == '\"')
			return ((ft_create_quoted_token_empty(t_qdata->raw_input, t_qdata->start)));
		else
			return (ft_create_unquoted_token(t_qdata->raw_input, t_qdata->start, end - t_qdata->start));
	}
}
