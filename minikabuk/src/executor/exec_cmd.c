#include "minishell.h"

void	execute_in_parent(char *cmd, t_minishell *minishell)
{
	t_token_list    *tmp;

	if (ft_strcmp(cmd, "cd") == 0)
		minishell->exit_status = ft_cd(minishell);
	else if (ft_strcmp(cmd, "export") == 0)
		minishell->exit_status = ft_export(minishell);
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

int	process_single_token(t_minishell *minishell, t_token_list **tmp)
{
	char	**cmd;
	int		saved_stdin;

	cmd = current_token(*tmp);
	if (has_redirect_or_heredoc(minishell))
	{
		saved_stdin = dup(STDIN_FILENO);
		if (handle_heredoc(minishell))
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			return (minishell->exit_status);
		}
		minishell->exit_status = handle_redirect(minishell, tmp);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		skip_redirect_tokens(tmp); 
		return (minishell->exit_status);
	}
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export") ||
		!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
		execute_in_parent(cmd[0], minishell);
	else if ((*tmp)->token->type != TOKEN_WORD)
		handle_fork_and_execute(minishell, cmd, *tmp);
	return (0);
}

int	execute_no_pipe(t_minishell *minishell, t_token_list *tmp)
{
	while (tmp)
	{
		process_single_token(minishell, &tmp);
		if (tmp && !has_redirect_or_heredoc(minishell))
			tmp = tmp->next;
	}
	return (minishell->exit_status);
}

int	execute_command(t_minishell *minishell)
{
	t_token_list	*tmp;
	int				return_value;

	tmp = minishell->token_list;
	return_value = 0;
	if (is_pipeline(minishell))
	{
		if (execute_pipe_line(minishell, 0))
			printf("Execute Error");
	}
	else
		return_value = execute_no_pipe(minishell, tmp);
	return (return_value);
}
