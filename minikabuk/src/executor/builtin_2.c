#include "executor.h"

int	ft_cd(t_minishell *minishell)
{
	char			*new_path;
	char			*cwd;
    int     		result;
	t_token_list	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		write(2, "Getcmd Failed", 13);
		return (1);
	}
    new_path = NULL;
	tmp = minishell->token_list;
	if (!tmp->next)
	{
		ft_cd_back_start(minishell);
		return (0);
	}
	result = ft_cd_util(tmp->next->token->value, cwd, new_path, minishell);
    if (result != 0)
        return (1);
	return (0);
}

int	ft_export(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	if (!tmp || !tmp->token)
		return (1);
	if (!tmp->next)
	{
		print_envs_alphabetic(minishell->envp);
		return (0);
	}
	while (tmp->next && tmp->next->token->type == TOKEN_WORD)
	{
		if (add_env(minishell, tmp->next->token->value))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(t_minishell *minishell, char *current_token)
{
	t_env	*prev;
	t_env	*it;
	
	if (!current_token)
		return (0);
	if (!is_valid_identifier(current_token))
	{
		write(2, "minishell: unset: `", 19);
		write(2, current_token, ft_strlen(current_token));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	prev = NULL;
	it = minishell->envp;
	while (it)
	{
		if (!ft_strcmp(it->key, current_token))
		{
			if (prev)
				prev->next = it->next;
			else
				minishell->envp = it->next;
			free(it->key);
			free(it->value);
			free(it);
			break;
		}
		prev = it;
		it = it->next;
	}
	return (0);
}

int	is_numeric(const char *str)
{
    int i = 0;
    if (!str || !str[0])
        return (1);
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

///////////////////////////////////////////////

static int	handle_space_in_arg(t_minishell *minishell)
{
    char	*arg;
    char	*space_pos;
    int		len;
    char	first_part[256];

    arg = minishell->token_list->next->token->value;
    space_pos = ft_strchr(arg, ' ');
    len = space_pos - arg;
    ft_strlcpy(first_part, arg, len + 1);
    if (!is_numeric(first_part))
    {
        write(2, "minishell: exit: too many arguments\n", 36);
        minishell->exit_status = 1;
        return (1);
    }
    else
    {
        write(2, "minishell: exit: ", 17);
        write(2, first_part, len);
        write(2, ": numeric argument required\n", 28);
        write(2, "exit\n", 5);
        free_for_exit(minishell);
        exit(255);
    }
}

static void	handle_error_exit(t_minishell *minishell, char *tmp)
{
    write(2, "minishell: exit: ", 17);
    if (!tmp)
        write(2, minishell->token_list->next->token->value, 
            ft_strlen(minishell->token_list->next->token->value));
    else
        write(2, tmp, ft_strlen(tmp));
    write(2, ": numeric argument required\n", 28);
    //write(2, "exit\n", 5);
    free_for_exit(minishell);
    exit(255);
}

int	handle_single_arg(t_minishell *minishell)
{
    if (minishell->token_list && minishell->token_list->next)
    {
        if (ft_strchr(minishell->token_list->next->token->value, ' '))
        {
            return (handle_space_in_arg(minishell));
        }
        else if (!is_numeric(minishell->token_list->next->token->value))
            return (ft_atoi(minishell->token_list->next->token->value) % 256);
        else
            return (255);
    }
    return (-1);
}

int	handle_quoted_args(t_minishell *minishell, char **tmp)
{
    if (minishell->token_list && minishell->token_list->next 
        && minishell->token_list->next->next && 
        minishell->token_list->next->next->token->quotes == 1)
    {
        *tmp = ft_strjoin(minishell->token_list->next->token->value, 
                        minishell->token_list->next->next->token->value);
        if (!is_numeric(*tmp))
            return (ft_atoi(*tmp) % 256);
        else
            return (255);
    }
    else if (minishell->token_list && minishell->token_list->next 
        && minishell->token_list->next->next&& 
        minishell->token_list->next->next->token->type == TOKEN_WORD)
    {
        write(2, "minishell: exit: too many arguments\n", 36);
        minishell->exit_status = 1;
        return (1);
    }
    return (-1);
}

int	ft_exit(t_minishell *minishell)
{
    int		exit_code;
    char	*tmp;
    int		result;

    exit_code = minishell->exit_status;
    tmp = NULL;
    result = handle_quoted_args(minishell, &tmp);
    if (result != -1)
        exit_code = result;
    else
    {
        result = handle_single_arg(minishell);
        if (result != -1)
            exit_code = result;
    }
    if (exit_code == 255)
    {
        handle_error_exit(minishell, tmp);
    }
    write(1, "exit\n", 5);
    free_for_exit(minishell);
    exit(exit_code);
}
