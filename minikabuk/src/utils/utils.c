#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	calloc_minishell(t_minishell *minishell)
{
	minishell->count = malloc(sizeof(t_count));
	if (!minishell->count)
	{
		perror("malloc");
		return ;
	}
	minishell->count->pipe_count = 0;
	minishell->count->redir_in_count = 0;
	minishell->count->redir_out_count = 0;
	minishell->count->append_count = 0;
	minishell->count->heredoc_count = 0;
}
void    reset_counts(t_minishell *minishell)
{
    if (!minishell || !minishell->count)
        return ;
    minishell->count->pipe_count = 0;
    minishell->count->redir_in_count = 0;
    minishell->count->redir_out_count = 0;
    minishell->count->append_count = 0;
    minishell->count->heredoc_count = 0;
}
