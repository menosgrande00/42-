#include "executor.h"

int	free_for_exit(t_minishell *minishell)
{
	free(minishell);
	return(0);
}

void	malloc_fd_and_pid(int ***fd, pid_t **pids, t_minishell *minishell)
{
	int	i;

	i = 0;
	*pids = (pid_t *)ft_calloc(sizeof(pid_t), (minishell->count->pipe_count + 1));
	if (!*pids)
		return;
	*fd = (int **)ft_calloc(2, sizeof(int *));
	if (!(*fd))
	{
		free(*pids);
		return ;
	}
	while (i < 2)
	{
		*fd = (int **)ft_calloc(2, sizeof(int));
		if (!(*fd)[i])
		{
			while (i-- >= 0)
				free((*fd)[i]);
			free(*pids);
			free(fd);
			return ;
		}
		i++;
	}
}

int ft_cd_util(char *current_token, char *cwd, char *new_path)
{
    if (current_token[0] == '/')
	{
		new_path = ft_strjoin(cwd, current_token);
		free(cwd);
		if (!new_path)
			return (1);
		if (chdir(new_path))
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", new_path);
			free(new_path);
			return(1);
		}
		free(new_path);
	}
	else
	{
		if (chdir(current_token))
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", current_token);
            free(cwd);
			return(1);
		}
		free(cwd);
	}
    return (0);
}

int	process_for_echo(t_token_list **tmp)
{	
	char	*current;
	char	*temp;
	int		return_value;

	current = ft_strdup("");
	if (!current)
		return (1);
	*tmp = (*tmp)->next;
	while (*tmp && (*tmp)->token->type == TOKEN_WORD)
	{
		if (ft_strlen(current) > 0)
		{
			temp = ft_strjoin(current, " ");
			free(current);
			current = temp;
		}
		temp = ft_strjoin(current, (*tmp)->token->value);
		free(current);
		current = temp;
		*tmp = (*tmp)->next;
	}
	return_value = ft_echo(current);
	free(current);
	return (return_value);
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
		ft_env(minishell);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(*cmd);
	return (1);
}