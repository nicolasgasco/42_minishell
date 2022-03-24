/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_special_chars_0.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:54:43 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:54:44 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checking for >>, <, and > */
int	ft_special_chars_are_valid(t_cdata *t_cdata)
{
	ft_expand_special_char(t_cdata, ">>");
	// ft_expand_special_char(t_cdata, "<<");
	ft_expand_special_char(t_cdata, "|");
	ft_expand_special_char(t_cdata, "<");
	ft_expand_special_char(t_cdata, ">");
	if (t_cdata->syntax_error == 1)
		return (0);
	else
	{
		ft_print_after_special_chars_expansion(t_cdata); // TBD
		return (1);
	}
}

/* Expansion of >> */
int	ft_expand_special_char(t_cdata *t_cdata, char *set)
{
	while (1)
	{
		if (!ft_found_special_chars_set(t_cdata, set))
			break ;
	}
	//TODO error
	return (1);
}

/* Iterating list untill all >> are expanded */
int	ft_found_special_chars_set(t_cdata *t_cdata, char *set)
{
	struct s_qnode	*curr;
	int				found_sym;

	found_sym = 0;
	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		if (!curr->q_type && ft_has_special_char_set(curr->str, set))
		{
			if (ft_strlen(curr->str) <= ft_strlen(set))
				t_cdata->syntax_error = 1;
			else
			{
				found_sym = 1;
				ft_split_special_char_node(curr, ft_strlen(set), set);
			}
			break ;
		}
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (found_sym);
}

/* Checking if the specific set is present in the string */
int	ft_has_special_char_set(char *str, char *set)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	len = ft_strlen(set);
	while (str[i + (len - 1)] != '\0')
	{
		k = i;
		j = 0;
		while (str[k] == set[j] && set[j] != '\0')
		{
			k++;
			j++;
		}
		if (set[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}
