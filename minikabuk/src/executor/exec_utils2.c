#include "minishell.h"

int	free_for_exit(t_minishell *minishell)
{
	free(minishell);
	return(0);
}

int	malloc_fd_and_pid(int ***fd, pid_t **pids, t_minishell *minishell)
{
	int	i;

	i = 0;
	*pids = (pid_t *)ft_calloc(sizeof(pid_t), (minishell->count->pipe_count + 1));
	if (!*pids)
		return (1);
	*fd = (int **)ft_calloc(minishell->count->pipe_count, sizeof(int *));
	if (!(*fd))
	{
		free(*pids);
		return (1);
	}
	i = -1;
	while (++i < minishell->count->pipe_count)
	{
		(*fd)[i] = (int *)ft_calloc(2, sizeof(int));
		if (!(*fd)[i])
		{
			while (i-- >= 0)
				free((*fd)[i]);
			free(*pids);
			free(*fd);
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

int exec_child(char **cmd, t_minishell *minishell)
{
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		return(process_for_echo(&minishell->token_list));
	return (0);
}
