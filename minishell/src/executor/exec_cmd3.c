/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:38:38 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/13 22:27:00 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_directory_and_permissions(t_minishell *minishell,
		char **cmd, char *path, char **env_array)
{
	struct stat	st;

	if (stat(path, &st) == 0 && is_dot(cmd))
	{
		if (S_ISDIR(st.st_mode))
		{
			free(path);
			free_double(env_array);
			exit(report_is_a_directory(minishell, cmd[0]));
		}
		else if (!(st.st_mode & S_IXUSR))
		{
			free(path);
			free_double(env_array);
			exit(report_perm_denied(minishell, cmd[0]));
		}
	}
}

static void	handle_path_errors_and_exit(t_minishell *minishell, char **cmd,
		char *path, char **env_array)
{
	if (is_dot(cmd))
	{
		free(path);
		free_double(env_array);
		exit(report_no_such_file(minishell, cmd[0]));
	}
	if (!path)
	{
		free_double(env_array);
		exit(report_cmd_not_found(minishell, cmd[0]));
	}
}

void	handle_errors_and_exit(t_minishell *minishell, char **cmd, char *path,
		char **env_array)
{
	check_directory_and_permissions(minishell, cmd, path, env_array);
	handle_path_errors_and_exit(minishell, cmd, path, env_array);
}

void	validate_and_execute(t_minishell *minishell, char **cmd, char *path)
{
	char	**env_array;
	int 	status;

	env_array = make_env_array(minishell);
	handle_errors_and_exit(minishell, cmd, path, env_array);
	if (minishell->exit_status)
	{
		status = minishell->exit_status;
		free_double(env_array);
		free_for_exit(minishell);
		exit(status);
	}
	execve(path, cmd, env_array);
	free(path);
	free_double(env_array);
	free_for_exit(minishell);
	exit(1);
}
