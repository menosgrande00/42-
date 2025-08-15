/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:15:21 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/15 22:51:02 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_heredoc(t_minishell *ms, char *delimiter, int write_fd , char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ms->fd_i >= 0)
		{
			while (ms->fd_i < ms->count->pipe_count)
			{
				free(ms->fd[ms->fd_i]);
				ms->fd_i++;
			}
			free(ms->fd);
			free(ms->pids);
		}
		if (cmd)
			free(cmd);
		heredoc_child(ms, delimiter, write_fd);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			ms->exit_status = 130;
			return (-1);
		}
		ms->exit_status = 0;
	}
	return (0);
}

int	handle_heredoc(t_minishell *ms , char **cmd)
{
	t_token_list	*tmp;
	int				pipe_fd[2];

	set_data(ms);
	pipe(pipe_fd);
	signal(SIGINT, SIG_IGN);
	tmp = ms->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC && tmp->next)
		{
			if (setup_heredoc(ms, tmp->next->token->value, pipe_fd[1], cmd) == -1)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	init_signal();
	return (0);
}
