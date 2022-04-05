#include "minishell.h"

t_sig    sig_data;

void    ft_handle_signals(int sig)
{
    if (sig_data.is_child == 0)
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
    else
    {
        printf("Handler. Child process. Minishell IS interactive\n");
        if (sig == SIGINT || sig == SIGQUIT)
        {
            printf("SIGINT OR SIGQUIT\n");
            // Free ?
            exit(3);
        }
    }
}

void    ft_shortcuts_events(void)
{
    struct sigaction    sa;

    if (sig_data.is_child == 0)
    {
        printf("Initializer. Main process. Minishell is NOT interactive\n");
        ft_ignore_signal(sa, SIGQUIT);
        sa.sa_handler = &ft_handle_signals;
        sigaction(SIGINT, &sa, NULL);
    }
    else
    {
        sa.sa_handler = &ft_handle_signals;
        sigaction(SIGQUIT, &sa, NULL);
        sigaction(SIGINT, &sa, NULL);
        printf("Initializer. Child process. Minishell IS interactive\n");

    }
}

/* When not interactive, ctr + \ is ignored */
void    ft_ignore_signal(struct sigaction sa, int sig)
{
    sa.sa_handler = SIG_IGN;
    sigaction(sig, &sa, NULL);
}
