#include "minishell.h"

t_sig    sig_data;

/* Handle for case when simulation is inside main process */
void    ft_handle_signals(int sig)
{
    printf("Handler. Parent process. Minishell is NOT interactive (%d)\n", getpid());
    if (sig == SIGINT)
    {
        printf("SIGINT in parent process (%d)\n", getpid());
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        return ;
    }
}

/* Handle for case when simulation is inside child process */
void    ft_handle_signals_interactive(int sig)
{
    printf("Handler. Child process. Minishell IS interactive (%d)\n", getpid());
    if (sig == SIGQUIT || sig == SIGINT)
    {
        printf("SIGINT or SIGQUIT in child process (%d)\n", getpid());
        // Free ?
        exit(3);
    }
}

/* Case when simulation is inside main process */
void    ft_shortcut_events(void)
{
    struct sigaction    sa;

    printf("Initializer. Main process. Minishell is NOT interactive (%d)\n", getpid());
    ft_ignore_signal(sa, SIGQUIT);
    sa.sa_handler = &ft_handle_signals;
    sigaction(SIGINT, &sa, NULL);
}

/* Case when simulation is inside child process) */
void    ft_shortcut_events_interactive(void)
{
    struct sigaction    sa_interactive;

    printf("Initializer. Child process. Minishell IS interactive (%d)\n", getpid());
    sa_interactive.sa_handler = &ft_handle_signals_interactive;
    sigaction(SIGQUIT, &sa_interactive, NULL);
    sigaction(SIGINT, &sa_interactive, NULL);
}

/* Make a process ignore all signals */
void    ft_ignore_all_signals(void)
{
    struct sigaction    sa;

    printf("Ignoring all signals (%d)\n", getpid());
    ft_ignore_signal(sa, SIGQUIT);
    ft_ignore_signal(sa, SIGINT);
}

/* When not interactive, ctr + \ is ignored */
void    ft_ignore_signal(struct sigaction sa, int sig)
{
    sa.sa_handler = SIG_IGN;
    sigaction(sig, &sa, NULL);
}
