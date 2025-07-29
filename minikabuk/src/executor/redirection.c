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
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
	}
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


static int	count_command_tokens(t_token_list *token_list)
{
	t_token_list	*tmp;
	int				count;

	count = 0;
	tmp = token_list;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_COMMAND || tmp->token->type == TOKEN_WORD)
		{
			count++;
			tmp = tmp->next;
		}
		else if (tmp->token->type == TOKEN_REDIRECT_IN || 
				 tmp->token->type == TOKEN_REDIRECT_OUT ||
				 tmp->token->type == TOKEN_APPEND ||
				 tmp->token->type == TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (count);
}

char	**extract_clean_command(t_token_list *token_list)
{
	t_token_list	*tmp;
	char			**cmd_args;
	int				count;
	int				i;

	count = count_command_tokens(token_list);
	if (count == 0)
		return (NULL);
	cmd_args = ft_calloc(count + 1, sizeof(char *));
	if (!cmd_args)
		return (NULL);
	tmp = token_list;
	i = 0;
	while (tmp && i < count)
	{
		if (tmp->token->type == TOKEN_COMMAND || tmp->token->type == TOKEN_WORD)
		{
			cmd_args[i] = ft_strdup(tmp->token->value);
			i++;
			tmp = tmp->next;
		}
		else if (tmp->token->type == TOKEN_REDIRECT_IN || 
				 tmp->token->type == TOKEN_REDIRECT_OUT ||
				 tmp->token->type == TOKEN_APPEND ||
				 tmp->token->type == TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
		else
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

///////////////////////////////

static int	setup_input_redirections(t_minishell *minishell, char *input_file, char *heredoc_delim)
{
	int	input_fd;

	if (heredoc_delim)
	{
		input_fd = setup_heredoc(heredoc_delim);
		if (input_fd == -1)
		{
		    write(2, "minishell: ", 11);
		    write(2, input_file, ft_strlen(input_file));
		    write(2, ": No such file or directory\n", 28);
			minishell->exit_status = 1;
		    exit (1);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (input_file)
	{
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
		{
			write(2, "minishell: ", 11);
			write(2, input_file, ft_strlen(input_file));
			write(2, ": No such file or directory\n", 28);
			minishell->exit_status = 1;
			exit (1);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	return (0);
}

static int	setup_output_redirections(t_minishell *minishell, char *output_file, char *append_file)
{
	int	output_fd;

	if (append_file)
	{
		output_fd = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (output_fd == -1)
		{
			write(2, "minishell: ", 11);
			write(2, append_file, ft_strlen(append_file));
			write(2, ": Permission denied\n", 20);
			minishell->exit_status = 1;
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
			write(2, "minishell: ", 11);
			write(2, output_file, ft_strlen(output_file));
			write(2, ": Permission denied\n", 20);
			minishell->exit_status = 1;
			return (1);
		}
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	return (0);
}

int	setup_all_redirections(t_minishell *minishell, char *input_file, char *output_file, char *append_file, char *heredoc_delim)
{
	if (setup_input_redirections(minishell, input_file, heredoc_delim))
		return (1);
	if (setup_output_redirections(minishell, output_file, append_file))
		return (1);
	return (0);
}

/////////////////////////////
///////////////BUNA BAKMAN LAZIM  BURADADDA BURADAATIYZ
static void	extract_redirect_files(t_token_list *tmp, char **input_file, 
                                char **output_file, char **append_file)
{
    while (tmp && tmp->token->type != TOKEN_PIPE)
    {
        if (tmp->token->type == TOKEN_REDIRECT_IN && tmp->next)
        {
            int fd = open(tmp->next->token->value, O_RDONLY);
            if (fd == -1)
            {
                write(2, "minishell: ", 11);
                write(2, tmp->next->token->value, ft_strlen(tmp->next->token->value));
                write(2, ": No such file or directory\n", 28);
                exit(1);
            }
            close(fd);
            *input_file = tmp->next->token->value;
            tmp = tmp->next;
        }
        else if (tmp->token->type == TOKEN_REDIRECT_OUT && tmp->next)
        {
            int fd = open(tmp->next->token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                write(2, "minishell: ", 11);
                write(2, tmp->next->token->value, ft_strlen(tmp->next->token->value));
                write(2, ": Permission denied\n", 20);
                exit(1);
            }
            close(fd);
            *output_file = tmp->next->token->value;
            tmp = tmp->next;
        }
        else if (tmp->token->type == TOKEN_APPEND && tmp->next)
        {
            int fd = open(tmp->next->token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                write(2, "minishell: ", 11);
                write(2, tmp->next->token->value, ft_strlen(tmp->next->token->value));
                write(2, ": Permission denied\n", 20);
                exit(1);
            }
            close(fd);
            *append_file = tmp->next->token->value;
            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
}

static char	*extract_heredoc_delim(t_token_list *tmp)
{
	while (tmp)
	{
		if (tmp->token->type == TOKEN_HEREDOC && tmp->next)
		{
			return (tmp->next->token->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

///////////////////////////////////////////////////

static int	execute_builtin_with_redirect(char **cmd, t_minishell *minishell)
{
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo_from_cmd_array(cmd));
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export") ||
			!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
		execute_in_parent(cmd[0], minishell);
	return (0);
}

static int	execute_external_command(char **cmd, t_minishell *minishell)
{
	char	*path;
	pid_t	pid;
	int		status;
	struct stat	st;

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
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, cmd, make_env_array(minishell)) == -1)
		{
			perror("minishell");
			minishell->exit_status = 126;
			exit(minishell->exit_status);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			minishell->exit_status = 1;
	}
	else
	{
		perror("fork");
		minishell->exit_status = 1;
	}
	return (minishell->exit_status);
}

int	execute_redirect_herodoc_child(t_minishell *minishell)
{
	char	**cmd;
	int		ret;

	cmd = extract_clean_command(minishell->token_list);
	if (!cmd || !cmd[0])
		return (1);
	if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd") ||
		!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "cd") ||
		!ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "unset") ||
		!ft_strcmp(cmd[0], "exit"))
	{
		ret = execute_builtin_with_redirect(cmd, minishell);
	}
	else
	{
		ret = execute_external_command(cmd, minishell);
	}
	for (int i = 0; cmd[i]; i++)
		free(cmd[i]);
	free(cmd);
	return (ret);
}

int	handle_redirect_or_heredoc(t_minishell *minishell, t_token_list **token_list)
{
	int		**fd;
	pid_t	*pids;
	int		ret;
	int		saved_stdin;
	int		saved_stdout;
	char	*input_file;
	char	*output_file;
	char	*append_file;
	char	*heredoc_delim;


	input_file = NULL;
	output_file = NULL;
	append_file = NULL;
	malloc_pid_redirect(&fd, &pids, minishell);
	if (!fd || !pids)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);	
	extract_redirect_files(*token_list, &input_file, &output_file, &append_file);
	heredoc_delim = extract_heredoc_delim(*token_list);
	ret = setup_all_redirections(minishell, input_file, output_file, append_file, heredoc_delim);
	if (ret == 0)
		ret = execute_redirect_herodoc_child(minishell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}