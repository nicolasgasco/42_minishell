#include "minishell.h"

static t_sdata sig_data;


void    ft_handle_signals(int sig)
{
    sig_data.sig = sig;
    if (sig == SIGINT)
    {
    }
}

void    ft_shortcuts_events(void)
{
    struct sigaction    sa;

    sa.sa_handler = &ft_handle_signals;
    sigaction(SIGINT, &sa, NULL);
}