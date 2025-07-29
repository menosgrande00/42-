#include "executor.h"

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
	i = 0;
	while (i < minishell->count->pipe_count)
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
		i++;
	}
	return (0);
}

void	ft_cd_back_start(t_minishell *minishell)
{
	t_env	*env;
	char	*home;

	env = minishell->envp;
	home = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
		{
			home = env->value;
			break;
		}
		env = env->next;
	}
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return;
	}
	if (chdir(home))
		perror("minishell: cd");
}

char	*find_home(t_minishell *minishell)
{
	char	*home;
	t_env	*env;

	home = NULL;
	env = minishell->envp;
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
		{
			home = env->value;
			break;
		}
		env = env->next;
	}
	return (home);
}

static int	ft_cd_back_one(char *cwd, char *new_path, t_minishell *minishell)
{
	int		i;
	char	**paths;
	char	*home;

	i = 0;
	paths = ft_split(cwd, '/');
	home = find_home(minishell);
	new_path = ft_strdup("");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		free(cwd);
		return (1);
	}
	if (!ft_strcmp(cwd, home))
		return (1);
	while (paths[i + 1])
	{
		new_path = ft_strjoin(new_path, "/");
		new_path = ft_strjoin(new_path, paths[i]);
		i++;
	}
	free(cwd);
	if (!new_path)
		return (1);
	if (chdir(new_path))
	{
		write(2, "minishell: cd: ", 15);
		write(2, new_path, ft_strlen(new_path));
		write(2, ": No such file or directory\n", 28);
		free(new_path);
		return(1);
	}
	free(new_path);
	return (0);
}

static int	ft_go_path(char *cwd, char *new_path, char *current_token)
{
	free(cwd);
	new_path = ft_strdup(current_token);
	if (!new_path)
		return (1);
	if (chdir(new_path))
	{
		write(2, "minishell: cd: ", 15);
		write(2, new_path, ft_strlen(new_path));
		write(2, ": No such file or directory\n", 28);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}
char	*ft_token_with_spaces(t_minishell *minishell)
{
	char	*input;
	int		i;

	i = ft_strlen(minishell->input);
	input = ft_strdup(ft_strnstr(minishell->input, "cd", i) + 2);
	i = 0;

	while (*input == ' ' || *input == '\t')
		input++;
	return (input);
}

int ft_cd_util(char *current_token, char *cwd, char *new_path, t_minishell *minishell)
{
	int	ret;

	ret = 0;
	if (current_token[0] == '/')
		ret = ft_go_path(cwd, new_path, current_token);
	else if (!ft_strcmp(current_token, ".."))
		ret = ft_cd_back_one(cwd, new_path, minishell);
	else if (!ft_strcmp(current_token, "."))
		free(cwd);
	else
	{
		current_token = ft_token_with_spaces(minishell);
		if (chdir(current_token))
		{
			if (errno == EACCES)
			{
				write(2, "minishell: cd: ", 15);
				write(2, current_token, ft_strlen(current_token));
				write(2, ": Permission denied\n", 20);
			}
			else
			{
				write(2, "minishell: cd: ", 15);
				write(2, current_token, ft_strlen(current_token));
				write(2, ": No such file or directory\n", 28);
			}
			free(cwd);
			return(1);
		}
		free(cwd);
	}
    return (ret);
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
		if ((*tmp)->token->value && (*tmp)->token->value[0] != '\0')
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
		}
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
		return (ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		return(process_for_echo(&minishell->token_list));
	return (0);
}

int is_valid_identifier(const char *name)
{
    int i;

    if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
        return (0);
    i = 1;
    while (name[i])
    {
        if ((!ft_isalnum(name[i]) && name[i] != '_') || (!ft_isalnum(name[i]) && name[i] != '\0'))
            return (0);
        i++;
    }
    return (1);
}

////////////////////////////////
static int	validate_and_parse_env(char *arg, char **key, char **value)
{
    char	*eq;

    if (!arg)
        return (0);
    eq = ft_strchr(arg, '=');
    if (eq)
    {
        *key = ft_substr(arg, 0, eq - arg);
        *value = ft_strdup(eq + 1);
    }
    else
    {
        *key = ft_strdup(arg);
        *value = ft_strdup("");
    }
    if (!is_valid_identifier(*key))
    {
        write(2, "minishell: export: `", 20);
        write(2, arg, ft_strlen(arg));
        write(2, "': not a valid identifier\n", 26);
        free(*key);
        free(*value);
        return (1);
    }
    return (0);
}

static t_env	*find_existing_env(t_env *envp, char *key)
{
    t_env	*it;

    it = envp;
    while (it)
    {
        if (!ft_strcmp(it->key, key))
            return (it);
        it = it->next;
    }
    return (NULL);
}

static void	add_new_env_node(t_minishell *minishell, char *key, char *value)
{
    t_env	*it;
    t_env	*last;

    it = ft_calloc(1, sizeof(*it));
    it->key = key;
    it->value = value;
    it->next = NULL;
    if (!minishell->envp)
        minishell->envp = it;
    else
    {
        last = minishell->envp;
        while (last->next)
            last = last->next;
        last->next = it;
    }
}

int	add_env(t_minishell *minishell, char *arg)
{
    char	*key;
    char	*value;
    t_env	*existing;
    int		ret;

    ret = validate_and_parse_env(arg, &key, &value);
    if (ret == 1)
    {
        minishell->exit_status = 1;
        return (1);
    }
    if (ret == 0 && !key)
        return (0);
    existing = find_existing_env(minishell->envp, key);
    if (existing)
    {
        free(existing->value);
        existing->value = value;
        free(key);
        return (0);
    }
    add_new_env_node(minishell, key, value);
    return (0);
}

//////////////////////////////

int	same_token_number(t_token_list **tmp)
{
	int 			count;
	t_token_list	*last;

	last = *tmp;
	count = 0;
	while (last && (last->token->type == TOKEN_COMMAND || 
			last->token->type == TOKEN_WORD))
	{
		count++;
		last = last->next;
	}
	return (count);
}

char **ft_same_tokens(t_token_list **tmp)
{
	int				count;
	char			**tokens;
	int				i = 0;

	count = same_token_number(tmp);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	while (*tmp && ((*tmp)->token->type == TOKEN_COMMAND || 
			(*tmp)->token->type == TOKEN_WORD))
	{
		tokens[i++] = ft_strdup((*tmp)->token->value);
		*tmp = (*tmp)->next;
	}
	tokens[i] = NULL;
	return (tokens);
}
int	ft_echo_from_cmd_array(char **cmd)
{
    int i = 1;
    int no_newline = 0;
    int first = 1;

    if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
    {
        no_newline = 1;
        i = 2;
    }
    while (cmd[i] &&
        ft_strcmp(cmd[i], ">>") != 0 &&
        ft_strcmp(cmd[i], ">") != 0 &&
        ft_strcmp(cmd[i], "<") != 0 &&
        ft_strcmp(cmd[i], "<<") != 0)
    {
        if (!first)
            write(1, " ", 1);
        write(1, cmd[i], ft_strlen(cmd[i]));
        first = 0;
        i++;
    }
    if (!no_newline)
        write(1, "\n", 1);
    return (0);
}