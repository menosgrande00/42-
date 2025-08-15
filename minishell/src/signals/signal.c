/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:01:28 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/15 18:47:24 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:29:27 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:29:28 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_minishell	*global_ms(t_minishell *ms)
{
	static t_minishell	*global_ms;

	if (ms)
		global_ms = ms;
	else
		return (global_ms);
	return (ms);
}

void	set_data(t_minishell *ms)
{
	global_ms(ms);
}

t_minishell	*get_data(void)
{
	return (global_ms(NULL));
}

void	ft_ctrl_c(int sig)
{
	g_signal_received = sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n^C\n", 4);
	rl_redisplay();
}

void	init_signal(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	simple_signal_handler(int sign)
{
	g_signal_received = sign;
	if (sign == SIGINT)
		write(1, "\n", 1);
}

int	check_signal(void)
{
	int	sig;

	sig = g_signal_received;
	g_signal_received = 0;
	return (sig);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "> ^C\n", 5);
	free_for_exit(get_data());
	exit(130);
}
