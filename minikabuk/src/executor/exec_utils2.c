/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:44:39 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/07 17:45:13 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_fd_and_pid(int ***fd, pid_t **pids, t_minishell *ms)
{
	int	i;

	*pids = (pid_t *)ft_calloc(sizeof(pid_t), (ms->count->pipe_count + 1));
	if (!*pids)
		return (1);
	*fd = (int **)ft_calloc(ms->count->pipe_count, sizeof(int *));
	if (!(*fd))
	{
		free(*pids);
		return (1);
	}
	i = -1;
	while (++i < ms->count->pipe_count)
	{
		(*fd)[i] = (int *)ft_calloc(2, sizeof(int));
		if (!(*fd)[i])
		{
			while (i-- >= 0)
				free((*fd)[i]);
			free(*fd);
			free(*pids);
			return (1);
		}
	}
	return (0);
}

int	is_pipeline(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	exec_child(char **cmd, t_minishell *minishell)
{
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		return (process_for_echo(&minishell->token_list));
	return (0);
}
