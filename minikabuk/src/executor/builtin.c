#include "executor.h"

int	ft_echo(char *current_token)
{
	int i;
	int a;
	int y;

	i = 0;
	y = 0;
	a = 0;
	while (current_token[i])
	{
		if (current_token[i] == '-' && current_token[i + 1] == 'n')
		{
			a = 1;
			break ;
		}
		i++;
	}
	if (a == 0)
		ft_printf("\n");
	while (current_token[y] || y == i)
	{
		ft_printf("%c", current_token[y]);
		y++;
	}
	return (0);
}

int ft_env(t_minishell *minishell)
{
	t_env *tmp;

	tmp = minishell->envp;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("Getpwd Failed");
		return (1);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}

