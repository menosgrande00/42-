#include "executor.h"

void	execute_in_parent(char *cmd, t_minishell *minishell)
{
	if (ft_strcmp(cmd, "cd") == 0)
		minishell->exit_status = ft_cd(minishell);
	else if (ft_strcmp(cmd, "export") == 0)
		minishell->exit_status = ft_export(minishell);
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		if (minishell->token_list->next && minishell->token_list->next->token->value == TOKEN_WORD)
			minishell->exit_status = ft_unset(minishell, minishell->token_list->next->token->value);
		else
			minishell->exit_status = 0;
	}
	else if (ft_strcmp(cmd, "exit") == 0)
		minishell->exit_status = ft_exit(minishell);
}

int	has_redirect_or_heredoc(t_minishell *minishell)
{
	if (minishell->count->heredoc_count > 0)
		return(1);
	else if(minishell->count->append_count > 0)
		return (1);
	else if(minishell->count->redir_in_count > 0)
		return (1);
	else if(minishell->count->redir_out_count > 0)
		return (1);
	return (0);
}

char	**make_env_array(t_minishell *minishell)
{
    char	**env_array;
    t_env	*tmp;
    int		i;
    int		size;
    char	*temp;

    size = 0;
    tmp = minishell->envp;
    while (tmp && ++size)
        tmp = tmp->next;
    env_array = malloc(sizeof(char *) * (size + 1));
    if (!env_array)
        return (NULL);
    i = 0;
    tmp = minishell->envp;
    while (tmp)
    {
        temp = ft_strjoin(tmp->key, "=");
        env_array[i] = ft_strjoin(temp, tmp->value);
        free(temp);
        tmp = tmp->next;
        i++;
    }
    env_array[i] = NULL;
    return (env_array);
}
///////////////////////////////////////////

int	is_dot(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[0][0] == '/')
		return (1);
	while (cmd[0][i] && cmd[0][i] == '.')
	{
		if (cmd[0][i + 1] && cmd[0][i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	execute_child_process(t_minishell *minishell, char **cmd, t_token_list **tmp)
{
    char	*path;
	struct stat	st;

    set_default_signals();
    if (!has_redirect_or_heredoc(minishell) && 
        (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd") ||
        !ft_strcmp(cmd[0], "echo")))
    {
        minishell->exit_status = exec_child(cmd, minishell);
        exit(minishell->exit_status);
    }
    path = get_path(minishell->envp, cmd[0]);
    if (!path && is_dot(cmd))
    {
        if (access(cmd[0], F_OK) == 0)
            path = ft_strdup(cmd[0]);
    }
	if (stat(path, &st) == 0 && is_dot(cmd))
    {
        if (S_ISDIR(st.st_mode))
        {
            write(2, "minishell: ", 11);
            write(2, cmd[0], ft_strlen(cmd[0]));
            write(2, ": is a directory\n", 17);
            free(path);
            exit(126);
        }
        else if (!(st.st_mode & S_IXUSR))
        {
            write(2, "minishell: ", 11);
            write(2, cmd[0], ft_strlen(cmd[0]));
            write(2, ": Permission denied\n", 20);
            free(path);
            exit(126);
        }
    }
    else if(is_dot(cmd))
    {
        // stat başarısız olduysa
        write(2, "minishell: ", 11);
        write(2, cmd[0], ft_strlen(cmd[0]));
        write(2, ": No such file or directory\n", 28);
        free(path);
        exit(127);
    }
	if (!path)
    {
        write(2, "minishell: ", 11);
        write(2, cmd[0], ft_strlen(cmd[0]));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    cmd = ft_same_tokens(tmp);
    execve(path, cmd, make_env_array(minishell));
    exit(1);
}

static int	handle_fork_and_execute(t_minishell *minishell, char **cmd, t_token_list *tmp)
{
    pid_t	pid;
    int		status;

    set_ignore_signals();
    pid = fork();
    if (pid == 0 && minishell->token_list->token->type == TOKEN_COMMAND)
    {
        execute_child_process(minishell, cmd, &tmp);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        minishell->exit_status = WEXITSTATUS(status);
    else
        minishell->exit_status = 1;
    init_signal();
    return (0);
}
static void	skip_redirect_tokens(t_token_list **tmp)
{
    while (*tmp)
    {
        if ((*tmp)->token->type == TOKEN_REDIRECT_IN || 
            (*tmp)->token->type == TOKEN_REDIRECT_OUT ||
            (*tmp)->token->type == TOKEN_APPEND ||
            (*tmp)->token->type == TOKEN_HEREDOC)
        {
            *tmp = (*tmp)->next;
            if (*tmp)
                *tmp = (*tmp)->next;
        }
        else if ((*tmp)->token->type == TOKEN_COMMAND || (*tmp)->token->type == TOKEN_WORD)
        {
            *tmp = (*tmp)->next;
        }
        else
            break;
    }
}

static int	process_single_token(t_minishell *minishell, t_token_list **tmp)
{
    char	**cmd;

    cmd = current_token(*tmp);
    if (has_redirect_or_heredoc(minishell))
    {
        minishell->exit_status = handle_redirect_or_heredoc(minishell, tmp);
        skip_redirect_tokens(tmp);
        return (minishell->exit_status);
    }
    else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export") ||
        !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
    {
        execute_in_parent(cmd[0], minishell);
    }
    else if ((*tmp)->token->type != TOKEN_WORD)
    {
        handle_fork_and_execute(minishell, cmd, *tmp);
    }
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

//////////////////////////////////////////

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
