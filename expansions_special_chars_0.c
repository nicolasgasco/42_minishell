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

int	ft_special_chars_are_valid(t_cdata *t_cdata)
{
	if (ft_detect_special_chars(t_cdata))
		ft_print_special_char_detected(); // TBD
	else
		ft_print_no_special_char_detected(); // TBD
	if (t_cdata->syntax_error)
	{
		ft_print_syntax_error(); // TBD
		return (0);
	}
	return (1);
}

/* Detect if pipes or redirections are present in the user input */
int	ft_detect_special_chars(t_cdata *t_cdata)
{
	int		i;
	char	*s;

	i = 1;
	s = t_cdata->line_expanded;
	if (ft_found_special_character(s[0]))
		return (ft_first_char_special(s, t_cdata));
	while (s[i + 1] != '\0')
	{
		if (ft_found_special_character(s[i]))
		{
			if (!ft_found_inv_char(s[i + 1]) && !ft_found_inv_char(s[i - 1]))
				return (1);
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
