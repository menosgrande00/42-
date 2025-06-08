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
		ft_printf("minishell: cd: HOME not set\n");
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
		ft_printf("minishell: cd: HOME not set\n");
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
		ft_printf("minishell: cd: %s: No such file or directory\n", new_path);
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
		ft_printf("minishell: cd: %s: No such file or directory\n", new_path);
		free(new_path);
		return(1);
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
    if (current_token[0] == '/')
		ft_go_path(cwd, new_path, current_token);
	else if (!ft_strcmp(current_token, ".."))
		ft_cd_back_one(cwd, new_path, minishell);
	else if (!ft_strcmp(current_token, "."))
		free(cwd);
	else
	{
		current_token = ft_token_with_spaces(minishell);
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

void add_env(t_minishell *minishell, char *arg)
{
    char  *key;
    char  *value;
    char  *eq;
    t_env *it;
	t_env *last;

    if (!arg)
        return;
    eq = ft_strchr(arg, '=');
    if (eq)
    {
        key   = ft_substr(arg, 0, eq - arg);
        value = ft_strdup(eq + 1);
    }
    else
    {
        key   = ft_strdup(arg);
        value = ft_strdup("");
    }
    if (!is_valid_identifier(key))
    {
        ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
        free(key);
        free(value);
        return;
    }
    it = minishell->envp;
    while (it)
    {
        if (!ft_strcmp(it->key, key))
        {
            free(it->value);
            it->value = value;
            free(key);
            return;
        }
        it = it->next;
    }
    it = ft_calloc(1, sizeof *it);
    it->key   = key;
    it->value = value;
    it->next  = NULL;
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

int	same_token_number(t_token_list *tmp)
{
	int count;

	count = 0;
	while (tmp && (tmp->token->type == TOKEN_COMMAND || 
			tmp->token->type == TOKEN_WORD))
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char **ft_same_tokens(t_minishell *minishell)
{
	t_token_list	*tmp;
	int				count;
	char			**tokens;
	int				i = 0;

	tmp = minishell->token_list;
	count = same_token_number(tmp);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	while (tmp && (tmp->token->type == TOKEN_COMMAND || 
			tmp->token->type == TOKEN_WORD))
	{
		tokens[i++] = ft_strdup(tmp->token->value);
		tmp = tmp->next;
	}
	tokens[i] = NULL;
	return (tokens);
}
