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

/* Handle for case when here docs is active */
void	ft_handle_signals_here_docs(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(g_ex_status);
	}
}

/* Case used for here docs */
void	ft_shortcut_events_here_docs(void)
{
	struct sigaction	sa_heredoc;

	memset(&sa_heredoc, 0, sizeof(struct sigaction));
	sa_heredoc.sa_handler = &ft_handle_signals_here_docs;
	ft_ignore_signal(sa_heredoc, SIGQUIT);
	sigaction(SIGINT, &sa_heredoc, NULL);
}

/* Make a process ignore all signals */
void	ft_ignore_all_signals(void)
{
	struct sigaction	sa;

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
