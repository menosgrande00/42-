#include "minishell.h"

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
