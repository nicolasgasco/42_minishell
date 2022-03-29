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

void	ft_free_loop_data(t_cdata *t_cdata)
{
	ft_free_quotes_data(t_cdata);
	ft_deallocate_tokens_list(&t_cdata->tokens_list);
}

void	ft_free_general_data(t_cdata *t_cdata)
{
	ft_free_prompt_data(t_cdata);
	ft_free_envp(t_cdata);
	ft_free_export(t_cdata);
}

void	ft_free_quotes_data(t_cdata *t_cdata)
{
	ft_deallocate_quotes_list(&t_cdata->t_qdata->quotes_list);
	free(t_cdata->t_qdata->raw_input);
	free(t_cdata->t_qdata);
}

void	ft_free_prompt_data(t_cdata *t_cdata)
{
	free(t_cdata->t_pdata->prompt_text);
	free(t_cdata->t_pdata->prompt_nl_text);
	free(t_cdata->t_pdata->hostname);
	free(t_cdata->t_pdata->username);
	free(t_cdata->t_pdata);
}
