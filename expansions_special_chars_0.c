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

/* Expand and isolate >>, <<, <, >, and | */
void	ft_expand_special_chars(t_cdata *t_cdata)
{
	ft_expand_special_char(t_cdata, ">>");
	ft_expand_special_char(t_cdata, "<<");
	ft_expand_special_char(t_cdata, "<");
	ft_expand_special_char(t_cdata, ">");
	ft_expand_special_char(t_cdata, "|");
	ft_print_after_special_chars_expansion(t_cdata); // TBD
	ft_remove_empty_nodes(t_cdata);
	ft_join_spaceless_nodes(t_cdata);
	ft_print_after_special_chars_expansion(t_cdata); // TBD	
}

/* Checking for >>, <, and > */
int	ft_special_chars_are_valid(t_cdata *t_cdata)
{
	if (ft_last_node_is_special_char(t_cdata)
		|| ft_found_adjacent_special_chars(t_cdata)
		|| ft_first_node_is_pipe(t_cdata))
	{
		t_cdata->syntax_error = 1;
		return (0);
	}	
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
		// ft_print_after_special_chars_expansion(t_cdata); // TBD
		if (!ft_found_special_chars_set(t_cdata, set))
			break ;
	}
	return (1);
}

/* Iterating list untill all >> are expanded */
int	ft_found_special_chars_set(t_cdata *t_cdata, char *set)
{
	struct s_qnode	*curr;
	int				s_char_i;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
		s_char_i = ft_has_special_char(curr->str, set);
		if (!curr->q_type && s_char_i >= 0)
		{
			if (ft_strcmp(curr->str, set) != 0
				&& ft_strlen(curr->str) > ft_strlen(set))
			{
				ft_split_s_char_node(curr, ft_strlen(set), set, s_char_i);
				return (1);
			}
		}
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (0);
}

int	ft_found_one_special_char(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}
