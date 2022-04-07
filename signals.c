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

t_sig sig_data;

/* Handle for case when simulation is inside main process */
void ft_handle_signals(int sig)
{
	fprintf(output, "Handler. Parent process. Minishell is NOT interactive (%d)\n", getpid());
	fflush(output);
	if (sig == SIGINT)
	{
		fprintf(output, "SIGINT in parent process (%d)\n", getpid());
		fflush(output);
		printf("\n");
		rl_on_new_line();
		// catch signal
		rl_replace_line("", 0);
		rl_redisplay();
		return;
	}
}

/* Handle for case when simulation is inside child process */
void ft_handle_signals_interactive(int sig)
{
	fprintf(output, "Handler. Child process. Minishell IS interactive (%d)\n", getpid());
	fflush(output);
	if (sig == SIGQUIT || sig == SIGINT)
	{
		fprintf(output, "SIGINT or SIGQUIT in child process (%d)\n", getpid());
		fflush(output);
		printf("\n");
		// exit(3);
	}
}

/* Case when simulation is inside main process */
void ft_shortcut_events(void)
{
	struct sigaction sa;

	fprintf(output, "Initializer. Main process. Minishell is NOT interactive (%d)\n", getpid());
	fflush(output);
	memset(&sa, 0, sizeof(struct sigaction));
	ft_ignore_signal(sa, SIGQUIT);
	sa.sa_handler = &ft_handle_signals;
	sigaction(SIGINT, &sa, NULL);
}

/* Case when simulation is inside child process) */
void ft_shortcut_events_interactive(void)
{
	struct sigaction sa_interactive;

	fprintf(output, "Initializer. Child process. Minishell IS interactive (%d)\n", getpid());
	fflush(output);
	memset(&sa_interactive, 0, sizeof(struct sigaction));
	sa_interactive.sa_handler = &ft_handle_signals_interactive;
	sigaction(SIGQUIT, &sa_interactive, NULL);
	sigaction(SIGINT, &sa_interactive, NULL);
}

/* Make a process ignore all signals */
void ft_ignore_all_signals(void)
{
	struct sigaction sa;

	fprintf(output, "Initializer. Child process. Minishell IS interactive (%d)\n", getpid());
	memset(&sa, 0, sizeof(struct sigaction));
	ft_ignore_signal(sa, SIGQUIT);
	ft_ignore_signal(sa, SIGINT);
}

/* When not interactive, ctr + \ is ignored */
void ft_ignore_signal(struct sigaction sa, int sig)
{
	sa.sa_handler = SIG_IGN;
	sigaction(sig, &sa, NULL);
}
