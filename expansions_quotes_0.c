/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_quotes_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:40:26 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:40:27 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if there are unclosed quotes */
int	ft_expanded_quotes_are_valid(t_cdata *t_cdata)
{
	if (t_cdata->syntax_error)
		return (0);
	return (1);
}

/* Input is tokenized according to quotes to see if they're unclosed or not */
void	ft_expand_quotes(t_cdata *t_cdata)
{
	ft_tokenize_quotes(t_cdata->t_qdata);
	if (t_cdata->t_qdata->d_open || t_cdata->t_qdata->s_open)
		t_cdata->syntax_error = 1;
}

/* 1/2 Raw input is parsed and tokenized in a linked list according to quotes */
void	ft_tokenize_quotes(t_qdata *t_qdata)
{
	int	i;

	i = 1;
	if (t_qdata->raw_input[0] == '\'')
		t_qdata->s_open = 1;
	else if (t_qdata->raw_input[0] == '\"')
		t_qdata->d_open = 1;
	while (t_qdata->raw_input[i] != '\0')
	{
		if (t_qdata->raw_input[i] == '\'' && t_qdata->d_open == 0)
			ft_tokenization_logic(t_qdata, i, '\'');
		else if (t_qdata->raw_input[i] == '\"' && t_qdata->s_open == 0)
			ft_tokenization_logic(t_qdata, i, '\"');
		i++;
	}
	if (t_qdata->d_open || t_qdata->s_open)
		ft_add_node_quotes(t_qdata, i, '\0');
	else if (t_qdata->start == 0 || t_qdata->start != i)
		ft_add_node_quotes(t_qdata, i, '\0');
}

/* 2/2 For both types of quotes, different tokenization logics are applied */
void	ft_tokenization_logic(t_qdata *t_qdata, int i, char quote)
{
	if (quote == '\'')
	{
		if (t_qdata->s_open == 0)
		{
			ft_tokenization_logic_unopened(t_qdata, i, quote);
			t_qdata->s_open = 1;
		}
		else if (t_qdata->s_open == 1)
			ft_tokenization_logic_opened(t_qdata, i, quote);
	}
	else if (quote == '\"')
	{
		if (t_qdata->d_open == 0)
			ft_tokenization_logic_unopened(t_qdata, i, quote);
		else if (t_qdata->d_open == 1)
			ft_tokenization_logic_opened(t_qdata, i, quote);
	}
}
