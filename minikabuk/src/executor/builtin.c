#include "executor.h"

int	ft_echo(char **tokens)
{
	int i;
	int newline = 1;
	int start_idx = 1;

	// -n flag kontrolü
	if (tokens[1] && ft_strcmp(tokens[1], "-n") == 0)
	{
		newline = 0;
		start_idx = 2;
	}
	
	// Tüm argümanları yazdır
	i = start_idx;
	while (tokens[i])
	{
		printf("%s", tokens[i]);
		if (tokens[i + 1])  // Son argüman değilse space ekle
			printf(" ");
		i++;
	}
	
	if (newline)
		printf("\n");
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

