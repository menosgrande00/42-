/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:15:21 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/07 18:15:22 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_errors(t_minishell *ms, int status, int pipe_fd)
{
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		ms->exit_status = 130;
		close(pipe_fd);
		return (-1);
	}
	else if (WIFSIGNALED(status))
	{
		ms->exit_status = 128 + WTERMSIG(status);
		close(pipe_fd);
		return (-1);
	}
	return (pipe_fd);
}

static int	heredoc_parent(t_minishell *ms, int pid, int pipe_fd[2])
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	init_signal();
	return (handle_heredoc_errors(ms, status, pipe_fd[0]));
}

static int	setup_heredoc(t_minishell *ms, char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc_child(ms, delimiter, pipe_fd[1]);
	}
	else if (pid > 0)
		return (heredoc_parent(ms, pid, pipe_fd));
	else
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (0);
}

int	handle_heredoc(t_minishell *ms)
{
	t_token_list	*tmp;
	int				fd;

	fd = -1;
	tmp = ms->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC && tmp->next)
		{
			if (fd != -1)
				close(fd);
			fd = setup_heredoc(ms, tmp->next->token->value);
			if (fd == -1 || ms->exit_status == 130)
				return (1);
		}
		tmp = tmp->next;
	}
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}
