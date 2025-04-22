#include "minishell.h"

static void	ft_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    pre_signals()
{
    signal(SIGINT, ft_ctrl_c);
    signal(SIGQUIT, SIG_IGN);
}