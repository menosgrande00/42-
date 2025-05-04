#include "minishell.h"

void	split_input(t_minishell *minishell)
{
	minishell->tokens = ft_split(minishell->input, ' ');
	if (!minishell->tokens)
	{
		perror("malloc");
		free(minishell->input);
		free(minishell->envp);
		free(minishell);
		exit(EXIT_FAILURE);
	}
}
