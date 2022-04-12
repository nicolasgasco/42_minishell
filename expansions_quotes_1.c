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
			ft_tokenization_logic_unopened_single_quote(t_qdata, i);
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

/* Util for function above encapsulating code for single quote case */
void	ft_tokenization_logic_unopened_single_quote(t_qdata *t_qdata, int i)
{
	if (t_qdata->d_open == 1)
		ft_add_node_quotes(t_qdata, i, '\0');
	else if (t_qdata->d_open == 0)
	{
		t_qdata->s_open = 1;
		ft_add_node_quotes(t_qdata, i, '\0');
	}
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
	memset(new_node, 0, sizeof(struct s_qnode));
	ft_popoulate_new_node_quotes(new_node, t_qdata, end, quote);
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

/* Util function to add all relevant proprierties to quoted node */
void	ft_popoulate_new_node_quotes(struct s_qnode *new_node, t_qdata *t_qdata,
		int end, char quote)
{
	new_node->str = ft_write_str_to_node(t_qdata, end);
	if ((quote && t_qdata->raw_input[end + 1]
			&& ft_isspace(t_qdata->raw_input[end + 1]))
		|| (!quote && t_qdata->raw_input[end]
			&& ft_isspace(t_qdata->raw_input[end])))
		new_node->is_spaced = 1;
	new_node->length = ft_strlen(new_node->str);
	new_node->q_type = quote;
	new_node->next = NULL;
}
