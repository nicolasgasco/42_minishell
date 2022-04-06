/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:12:28 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/21 16:12:30 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_output_loop_error_message(t_cdata *t_cdata, char *message)
{
	if (t_cdata->syntax_error == 1)
	{
		ft_free_quotes_data(t_cdata);
		if (*message)
			printf("Syntax error: %s\n", message);
	}
	return (1);
}
