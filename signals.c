#include "minishell.h"

int	minishell_sig;

void    ft_handle_signals(int sig)
{
    printf("%d\n", sig);
    minishell_sig = sig;
    if (minishell_sig == SIGINT)
    {
        printf("\n%s", "> ");
    }
}

void    ft_shortcuts_events(void)
{
    struct sigaction    sa;

    sa.sa_handler = &ft_handle_signals;
    sigaction(SIGINT, &sa, NULL);
}