#include "minishell.h"

void    ft_handle_signals(int sig)
{
    if (sig == SIGQUIT)
    {
        // Continue
    }
    else if (sig == SIGINT)
    {
        // g_sig.status = 1;
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        return ;
    }
}

void    ft_shortcuts_events(void)
{
    struct sigaction    sa;

    // Add logic for when inside a process
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
    sa.sa_handler = &ft_handle_signals;
    sigaction(SIGINT, &sa, NULL);
}
