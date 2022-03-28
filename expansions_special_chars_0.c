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
int ft_special_chars_are_valid(t_cdata *t_cdata)
{
	ft_expand_special_char(t_cdata, "<");
	ft_expand_special_char(t_cdata, ">");
	ft_expand_special_char(t_cdata, ">>");
	ft_expand_special_char(t_cdata, "<<");
	ft_expand_special_char(t_cdata, "|");
	if (t_cdata->syntax_error == 1)
		return (0);
	else
	{
		ft_print_after_special_chars_expansion(t_cdata); // TBD
		return (1);
	}
}

/* Expansion of >> */
int ft_expand_special_char(t_cdata *t_cdata, char *set)
{
	while (1)
	{
		ft_print_after_special_chars_expansion(t_cdata); // TBD
		if (!ft_found_special_chars_set(t_cdata, set))
			break ;
	}
	// TODO error
	return (1);
}

/* Iterating list untill all >> are expanded */
int ft_found_special_chars_set(t_cdata *t_cdata, char *set)
{
	struct s_qnode *curr;
	int				s_char_i;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		s_char_i = ft_has_special_char(curr->str, set);
		if (!curr->q_type && s_char_i >= 0)
		{
			if (ft_strcmp(curr->str, set) != 0)
			{
				ft_split_special_char_node(curr, ft_strlen(set), set, s_char_i);
				return (1);
			}
		}
		if (curr->next == NULL)
			break;
		else
			curr = curr->next;
	}
	return (0);
}

/* Checking if the specified set or character are in the string */
int ft_has_special_char(char *str, char *set)
{
	if (ft_strlen(set) == 2)
		return (ft_find_special_char_set(str, set));
	else
		return (ft_find_special_char_single(str, set[0]));
}

/* Checking if the specified set is in the string */
int	ft_find_special_char_set(char *str, char *set)
{
	int i;
	int j;
	int k;
	int len;

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
		if (str[k] != set[0] && set[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
