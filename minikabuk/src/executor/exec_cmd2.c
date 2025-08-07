/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:38:35 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/07 17:42:29 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_minishell *ms, char **cmd, t_token_list **tmp)
{
	char	*path;
	char	**new_cmd;

	set_default_signals();
	if (!has_redirect_or_heredoc(ms)
		&& (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd")
			|| !ft_strcmp(cmd[0], "echo")))
	{
		ms->exit_status = exec_child(cmd, ms);
		exit(ms->exit_status);
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
}

int	handle_fork_and_execute(t_minishell *ms, char **cmd, t_token_list *tmp)
{
	pid_t	pid;
	int		status;

	set_ignore_signals();
	pid = fork();
	if (pid == 0 && ms->token_list->token->type == TOKEN_COMMAND)
		execute_child(ms, cmd, &tmp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->exit_status = WEXITSTATUS(status);
	else
		ms->exit_status = 1;
	return (0);
}
