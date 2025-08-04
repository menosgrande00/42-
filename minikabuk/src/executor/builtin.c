#include "executor.h"

int	ft_echo(char *current_token)
{
	int i;
	int no_newline;

	i = 0;
	no_newline = 0;
	while (current_token[i] == '-' && current_token[i + 1] == 'n')
	{
		int j = i + 2;
		
		while (current_token[j] == 'n')
			j++;
		if (current_token[j] == ' ' || current_token[j] == '\t' || current_token[j] == '\0')
		{
			no_newline = 1;
			i = j;
			while (current_token[i] == ' ' || current_token[i] == '\t')
				i++;
		}
		else
			break;
	}
	while (current_token[i])
	{
		write(1, &current_token[i], 1);
		i++;
	}
	if (!no_newline)
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

