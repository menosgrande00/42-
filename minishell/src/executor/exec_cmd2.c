/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:38:35 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/13 22:40:06 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_minishell *ms, char **cmd, t_token_list **tmp)
{
	char	*path;
	char	**new_cmd;
	int		status;
	t_token_list *saved_head;

	set_default_signals();
	if (!has_redirect_or_heredoc(ms)
		&& (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd")
			|| !ft_strcmp(cmd[0], "echo")))
	{
		saved_head = ms->token_list;
		ms->exit_status = exec_child(cmd, ms);
		ms->token_list = saved_head;
		if (cmd)
			free(cmd);
		{
			status = ms->exit_status;
			free_for_exit(ms);
			exit(status);
		}
	}
	path = get_path(ms->envp, cmd[0]);
	if (!path && is_dot(cmd))
	{
		if (access(cmd[0], F_OK) == 0)
			path = ft_strdup(cmd[0]);
	}
	new_cmd = ft_same_tokens(tmp);
	if (new_cmd)
	{
		free_double(cmd);
		cmd = new_cmd;
	}
	validate_and_execute(ms, cmd, path);
	if (cmd)
		free_double(cmd);
	{
		status = ms->exit_status;
		free_for_exit(ms);
		exit(status);
	}
}

int	handle_fork_and_execute(t_minishell *ms, char **cmd, t_token_list *tmp)
{
	pid_t	pid;
	int		status;
	int		sig;

	set_ignore_signals();
	pid = fork();
	if (pid == 0 && ms->token_list->token->type == TOKEN_COMMAND)
		execute_child(ms, cmd, &tmp);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit: 3\n", 8);
		else if (sig == SIGINT)
			write(1, "^C\n", 3);
		ms->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
	return (0);
}

void	execute_in_parent(char *cmd, t_minishell *minishell)
{
	t_token_list	*tmp;

	if (ft_strcmp(cmd, "cd") == 0)
		minishell->exit_status = ft_cd(minishell);
	else if (ft_strcmp(cmd, "export") == 0)
		minishell->exit_status = ft_export(minishell);
	else if (ft_strcmp(cmd, "env") == 0)
		minishell->exit_status = ft_env(minishell);
	else if (ft_strcmp(cmd, "pwd") == 0)
		minishell->exit_status = ft_pwd();
	else if (ft_strcmp(cmd, "echo") == 0)
		minishell->exit_status = process_for_echo(&minishell->token_list);
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		minishell->exit_status = 0;
		tmp = minishell->token_list->next;
		while (tmp && tmp->token->type == TOKEN_WORD)
		{
			if (ft_unset(minishell, tmp->token->value))
				minishell->exit_status = 1;
			tmp = tmp->next;
		}
	}
	else if (ft_strcmp(cmd, "exit") == 0)
		minishell->exit_status = ft_exit(minishell);
}
