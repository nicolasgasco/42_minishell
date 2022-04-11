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

/* Handle for case when simulation is inside main process */
void	ft_handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

/* Case when simulation is inside main process */
void	ft_shortcut_events(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	ft_ignore_signal(sa, SIGQUIT);
	sa.sa_handler = &ft_handle_signals;
	sigaction(SIGINT, &sa, NULL);
}

/* Handle for case when simulation is inside child process */
void	ft_handle_signals_interactive(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		printf("\n");
}

/* Case when simulation is inside child process) */
void	ft_shortcut_events_interactive(void)
{
	struct sigaction	sa_interactive;

	memset(&sa_interactive, 0, sizeof(struct sigaction));
	sa_interactive.sa_handler = &ft_handle_signals_interactive;
	sigaction(SIGQUIT, &sa_interactive, NULL);
	sigaction(SIGINT, &sa_interactive, NULL);
}
