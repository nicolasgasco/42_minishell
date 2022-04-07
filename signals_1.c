/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:13:57 by ngasco            #+#    #+#             */
/*   Updated: 2022/04/07 11:13:59 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Make a process ignore all signals */
void	ft_ignore_all_signals(void)
{
	struct sigaction	sa;

	fprintf(output, "Initializer child. Minishell IS interactive (%d)\n",
		getpid());
	memset(&sa, 0, sizeof(struct sigaction));
	ft_ignore_signal(sa, SIGQUIT);
	ft_ignore_signal(sa, SIGINT);
}

/* When not interactive, ctr + \ is ignored */
void	ft_ignore_signal(struct sigaction sa, int sig)
{
	sa.sa_handler = SIG_IGN;
	sigaction(sig, &sa, NULL);
}
