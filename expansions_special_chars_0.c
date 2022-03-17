/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_special_chars_0.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:32:31 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:32:32 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_special_chars(t_cdata *t_cdata)
{
	struct s_qnode	*curr;

	curr = t_cdata->t_qdata->quotes_list;
	while (1)
	{
        if (!curr->q_type && ft_detect_special_chars(t_cdata, curr->str))
        {
			ft_print_special_char_detected();
            break;
        }
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
}

/* Detect if pipes or redirections are present in the user input */
int	ft_detect_special_chars(t_cdata *t_cdata, char *s)
{
	int		i;

	i = 1;
	if (ft_found_special_character(s[0]))
		return (ft_first_char_special(s, t_cdata));
	while (s[i + 1] != '\0')
	{
		if (ft_found_special_character(s[i]))
		{
			if (!ft_found_inv_char(s[i + 1]) && !ft_found_inv_char(s[i - 1]))
				return (i);
			t_cdata->syntax_error = 1;
			return (0);
		}
		i++;
	}
	if (ft_found_special_character(s[i]))
		return (ft_last_char_special(s, i, t_cdata));
	return (0);
}

/* Utility for previous function, case where first char is special */
int	ft_first_char_special(char *str, t_cdata *t_cdata)
{
	if (!ft_found_inv_char(str[1]))
		return (1);
	t_cdata->syntax_error = 1;
	return (0);
}

/* Utility for previous function, case where last char is special */
int	ft_last_char_special(char *str, int i, t_cdata *t_cdata)
{
	if (!ft_found_inv_char(str[i - 1]))
		return (1);
	t_cdata->syntax_error = 1;
	return (0);
}
