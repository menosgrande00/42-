/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:52:13 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/14 18:19:03 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_child_fds(int **fd, int pipe_count,
			int read_index, int write_index)
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		if (j != read_index)
		{
			close(fd[j][0]);
		}
		if (j != write_index)
		{
			close(fd[j][1]);
		}
		free(fd[j]);
		j++;
	}
	free(fd);
}

static void	setup_pipe_and_fork(t_minishell *minishell,
			int i, pid_t *pids, int **fd)
{
	int	read_index;

	pids[i] = fork();
	if (pids[i] == 0)
	{
		set_default_signals();
		read_index = -1;
		if (i > 0 && !has_input_redirect_or_heredoc(minishell))
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			read_index = i - 1;
		}
		if (i < minishell->count->pipe_count)
			dup2(fd[i][1], STDOUT_FILENO);
		close_child_fds(fd, minishell->count->pipe_count, read_index, i);
		free(pids);
		execute_pipe_child(minishell);
	}
}

static void	close_pipes_for_segment(int i, int **fd, int pipe_count)
{
	if (i > 0)
		close(fd[i - 1][0]);
	if (i < pipe_count)
		close(fd[i][1]);
}

static t_token_list	*advance_token_list(t_token_list *tmp)
{
	if (tmp)
	{
		while (tmp && tmp->token->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->token->type == TOKEN_PIPE)
		{
			tmp = tmp->next;
			if (!tmp)
			{
				perror("minishell");
				return (NULL);
			}
		}
	}
	return (tmp);
}

int	processor(t_minishell *minishell, pid_t *pids, int **fd)
{
	int				i;
	int				saved_stdin;
	t_token_list	*tmp;
	t_token_list	*head;

	i = -1;
	head = minishell->token_list;
	tmp = head;
	while (++i < minishell->count->pipe_count + 1)
	{
		minishell->token_list = tmp;
		saved_stdin = dup(STDIN_FILENO);
		if (handle_heredoc(minishell))
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			return (1);
		}
		setup_pipe_and_fork(minishell, i, pids, fd);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		close_pipes_for_segment(i, fd, minishell->count->pipe_count);
		tmp = advance_token_list(tmp);
	}
	minishell->token_list = head;
	return (0);
}
