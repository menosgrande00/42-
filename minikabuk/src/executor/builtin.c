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
			y = 3;
			break ;
		}
		i++;
	}
    while (current_token[y] || y == i - 1)
    {
        write(1, &current_token[y], 1);
        y++;
    }
    if (a == 0)
        write(1, "\n", 1);
    return (0);
}

int ft_env(t_minishell *minishell)
{
	t_env *tmp;

	tmp = minishell->envp;
	while (tmp)
	{
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
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
		write(2, "Getpwd Failed", 13);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

