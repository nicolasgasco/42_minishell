/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:26:04 by ngasco            #+#    #+#             */
/*   Updated: 2022/03/14 11:26:05 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_loop_data(c_data *c_data)
{
	ft_free_quotes_data(c_data);
	free(c_data->line_expanded);
	ft_deallocate_tokens_list(&c_data->tokens_list);
}

void	ft_free_loop_data_quotes_error(c_data *c_data)
{
	ft_free_quotes_data(c_data);
	free(c_data->line_expanded);
}

void	ft_free_general_data(c_data *c_data)
{
	ft_free_prompt_data(c_data);
}

void	ft_free_quotes_data(c_data *c_data)
{
	ft_deallocate_quotes_list(&c_data->q_data->quotes_list);
	free(c_data->q_data->raw_input);
	free(c_data->q_data);
}

void	ft_free_prompt_data(c_data *c_data)
{
	free(c_data->p_data->prompt_text);
	free(c_data->p_data);
}
