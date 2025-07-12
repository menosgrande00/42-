#include "minishell.h"

void	free_cmd_path(char **cmd_path, int i)
{
	while (cmd_path[i])
	{
		free(cmd_path[i]);
		i++;
	}
	free(cmd_path);
}

char	*get_path(t_env *envp, char *cmd)
{
	char	**paths;
	char	*path;
	t_env	*tmp_env;
	int		i;

	i = 0;
	tmp_env = envp;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "PATH"))
		{
			paths = ft_split(tmp_env->value, ':');
			if (!paths)
				return (NULL);
			while (paths[i])
			{
				path = ft_strjoin(paths[i], "/");
				path = ft_strjoin(path, cmd);
				if (access(path, X_OK) == 0)
				{
					free_cmd_path(paths, i);
					return (path);
				}
				i++;
			}
			free_cmd_path(paths, i);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*process_env(t_minishell *minishell, char *cmd, char **cmd_path)
{
	t_env	*tmp_env;

	tmp_env = minishell->envp;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, cmd))
		{
			*cmd_path = get_path(minishell->envp, cmd);
			return (tmp_env->value);
		}
		tmp_env = tmp_env->next;
	}
	if (!tmp_env)
		printf("minishell: %s: No such file or directory\n", cmd);
	return (NULL);
}

void	malloc_pid_redirect(int ***fd, pid_t **pids, t_minishell *minishell)
{
	int	i;

	i = 0;
	*pids = (pid_t *)ft_calloc(sizeof(pid_t), (minishell->count->redir_in_count +
												minishell->count->redir_out_count +
												minishell->count->append_count +
												minishell->count->heredoc_count + 1));
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
		(*fd)[i] = (int *)ft_calloc(2, sizeof(int));
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

char **extract_clean_command(t_token_list *token_list)
{
	t_token_list *tmp;
	char **cmd_args;
	int count = 0;
	int i = 0;
	int skip_next = 0;
    
	tmp = token_list;
	while (tmp)
	{
		if (skip_next)
		{
			skip_next = 0; // Flag'i sıfırla
        	tmp = tmp->next;
			continue;
		}
		if (tmp->token->type == TOKEN_COMMAND || tmp->token->type == TOKEN_WORD)
            count++;
        else if (tmp->token->type == TOKEN_REDIRECT_IN || 
                 tmp->token->type == TOKEN_REDIRECT_OUT ||
                 tmp->token->type == TOKEN_APPEND ||
                 tmp->token->type == TOKEN_HEREDOC)
            skip_next = 1;
        tmp = tmp->next;
    }
	cmd_args = ft_calloc(count + 1, sizeof(char *));
	tmp = token_list;
	skip_next = 0;
	while (tmp && i < count)
	{
		if (skip_next)
		{
			skip_next = 0;
			tmp = tmp->next;
			continue;
		}
		if (tmp->token->type == TOKEN_COMMAND || tmp->token->type == TOKEN_WORD)
		{
			cmd_args[i] = ft_strdup(tmp->token->value);
			i++;
		}
        else if (tmp->token->type == TOKEN_REDIRECT_IN || 
                 tmp->token->type == TOKEN_REDIRECT_OUT ||
                 tmp->token->type == TOKEN_APPEND ||
                 tmp->token->type == TOKEN_HEREDOC)
            skip_next = 1;
        tmp = tmp->next;
    }
    return (cmd_args);
}

int setup_heredoc(char *delimiter)
{
    int pipe_fd[2];
    char *line;
    
    if (pipe(pipe_fd) == -1)
        return (-1);
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}

int setup_all_redirections(char *input_file, char *output_file, char *append_file, char *heredoc_delim)
{
	int input_fd;
	int output_fd;

	if (heredoc_delim)
	{
	    input_fd = setup_heredoc(heredoc_delim);
	    if (input_fd == -1)
	        return (1);
	    dup2(input_fd, STDIN_FILENO);
	    close(input_fd);
	}
	if (input_file)
	{
	    input_fd = open(input_file, O_RDONLY);
	    if (input_fd == -1)
	    {
	        printf("minishell: %s: No such file or directory\n", input_file);
	        return (1);
	    }
	    dup2(input_fd, STDIN_FILENO);
	    close(input_fd);
	}
	if (append_file)
	{
	    output_fd = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	    if (output_fd == -1)
	    {
	    	printf("minishell: %s: Permission denied\n", append_file);
	        return (1);
	    }
	    dup2(output_fd, STDOUT_FILENO);
	    close(output_fd);
	}
	else if (output_file)
	{
	    output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	    if (output_fd == -1)
	    {
			printf("minishell: %s: Permission denied\n", output_file);
	        return (1);
	    }
	    dup2(output_fd, STDOUT_FILENO);
	    close(output_fd);
	}
	return (0);
}

int handle_redirect_or_heredoc(t_minishell *minishell, t_token_list **token_list)
{
    int **fd;
    pid_t *pids;
    int ret = 0;
    t_token_list *tmp;

    char *input_file = NULL;
    char *output_file = NULL;
    char *append_file = NULL;
    char *heredoc_delim = NULL;
    int saved_stdin;
    int saved_stdout;

    tmp = *token_list;
    malloc_pid_redirect(&fd, &pids, minishell);
    if (!fd || !pids)
        return (1);

    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);

    while (tmp)
    {
        if (tmp->token->type == TOKEN_REDIRECT_IN && tmp->next)
        {
            input_file = tmp->next->token->value;
            tmp = tmp->next;
        }
        else if (tmp->token->type == TOKEN_REDIRECT_OUT && tmp->next)
        {
            output_file = tmp->next->token->value;
            tmp = tmp->next;
        }
        else if (tmp->token->type == TOKEN_APPEND && tmp->next)
        {
            append_file = tmp->next->token->value;
            tmp = tmp->next;
        }
        else if (tmp->token->type == TOKEN_HEREDOC && tmp->next)
        {
            heredoc_delim = tmp->next->token->value;
            tmp = tmp->next;
        }
		ret = setup_all_redirections(input_file, output_file, 
                            append_file, heredoc_delim);
        tmp = tmp->next;
		
    }
    if (ret == 0)
        ret = execute_redirect_herodoc_child(minishell);
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    return (ret);
}

int execute_redirect_herodoc_child(t_minishell *minishell)
{
	char **cmd;
	char *path;

	cmd = extract_clean_command(minishell->token_list);
	if (!ft_strcmp(cmd[0], "env"))
		return(ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return(ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		return(process_for_echo(&minishell->token_list));
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export") ||
			!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit")) 
			execute_in_parent(cmd[0], minishell);
	else
	{
		pid_t pid;
		int status;

		path = get_path(minishell->envp, cmd[0]);
		if (!path)
		{
		    printf("minishell: %s: command not found\n", cmd[0]);
		    return (127);
		}

		pid = fork();
		if (pid == 0)
		{
		    if (execve(path, cmd, make_env_array(minishell)) == -1)
		    {
		        perror("minishell");
		        exit(126);
		    }
		}
		else if (pid > 0)
		{
		    waitpid(pid, &status, 0);
		    if (WIFEXITED(status))
		        return (WEXITSTATUS(status));
		    else
		        return (1);
		}
		else
		{
	   		perror("fork");
		    return (1);
		}
	}
	return (0);
}
