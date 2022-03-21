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

void	ft_output_loop_error_message(t_cdata *t_cdata, char *message)
{
	ft_free_quotes_data(t_cdata);
	printf("Syntax error: %s\n", message);
}
