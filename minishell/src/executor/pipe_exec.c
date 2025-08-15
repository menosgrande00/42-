/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:51:21 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/15 18:45:29 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe_builds(t_minishell *minishell, char **cmd)
{
	int				i;
	int 			status;
	t_token_list	*head;

	head = minishell->token_list;
	if (!ft_strcmp(cmd[0], "env"))
		minishell->exit_status = ft_env(minishell);
	else if (!ft_strcmp(cmd[0], "pwd"))
		minishell->exit_status = ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo"))
		minishell->exit_status = process_for_echo(&minishell->token_list);
	else if (!ft_strcmp(cmd[0], "export"))
		minishell->exit_status = ft_export(minishell);
	else if (!ft_strcmp(cmd[0], "cd"))
		minishell->exit_status = ft_cd(minishell);
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		minishell->exit_status = 0;
		i = 0;
		while (cmd[++i])
		{
			if (ft_unset(minishell, cmd[i]))
				minishell->exit_status = 1;
		}
	}
	else if (!ft_strcmp(cmd[0], "exit"))
		minishell->exit_status = ft_exit(minishell);
	if (cmd)
		free(cmd);
	status = minishell->exit_status;
	minishell->token_list = head;
	free_for_exit(minishell);
	exit(status);
}

static void	handle_redirection(t_minishell *minishell)
{
	int status;

	if (has_redirect(minishell))
	{
		minishell->exit_status = handle_redirect(minishell,
			&minishell->token_list);
		status = minishell->exit_status;
		free_for_exit(minishell);
		exit(status);
	}
}

static void	execute_execve(t_minishell *minishell, char **cmd)
{
	char	*path;
	char	**env_array;
	int		status;

	path = get_path(minishell->envp, cmd[0]);
	if (!path)
	{
		if (ft_strcmp(cmd[0], "<<"))
			report_cmd_not_found(minishell, cmd[0]);
		if (cmd)
			free(cmd);
		status = 127;
		free_for_exit(minishell);
		exit(status);
	}
	if (cmd)
		free(cmd);
	cmd = ft_same_tokens(&minishell->token_list);
	env_array = make_env_array(minishell);
	minishell->exit_status = execve(path, cmd, env_array);
	free(path);
	free_double(cmd);
	free_double(env_array);
	status = 126;
	free_for_exit(minishell);
	exit(status);
}

void	execute_pipe_child(t_minishell *minishell)
{
	char	**cmd;

	handle_redirection(minishell);
	cmd = current_token(minishell->token_list);
	if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd")
		|| !ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "exit"))
		execute_pipe_builds(minishell, cmd);
	else
		execute_execve(minishell, cmd);
}
