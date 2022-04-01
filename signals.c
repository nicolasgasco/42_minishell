#include "minishell.h"

extern t_sig    sig_data;

void    ft_handle_signals(int sig)
{
    if (sig == SIGQUIT)
    {
        printf("%s", sig_data.prompt_text);
        return ;
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

    sa.sa_handler = &ft_handle_signals;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}
