#include "minishell.h"

static int	handle_space_in_arg(t_minishell *minishell)
{
	char	*arg;
	char	*space_pos;
	int		len;
	char	*first_part;

	first_part = malloc(256);
	arg = minishell->token_list->next->token->value;
	space_pos = ft_strchr(arg, ' ');
	len = space_pos - arg;
	ft_strlcpy(first_part, arg, len + 1);
	if (!is_numeric(first_part))
	{
		free(first_part);
		return (report_error(minishell,
				"minishell: unset: not a valid identifier", ERR_INVALID_ARG));
	}
	else
	{
		report_num_arg_req(minishell, first_part, len);
		free(first_part);
		free_for_exit(minishell);
		exit(minishell->exit_status);
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
	free_for_exit(minishell);
	exit(255);
}

int	handle_single_arg(t_minishell *minishell)
{
	if (minishell->token_list && minishell->token_list->next)
	{
		if (ft_strchr(minishell->token_list->next->token->value, ' '))
			return (handle_space_in_arg(minishell));
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
		handle_error_exit(minishell, tmp);
	write(1, "exit\n", 5);
	free_for_exit(minishell);
	exit(exit_code);
}
