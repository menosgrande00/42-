#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	calloc_minishell(t_minishell *minishell)
{
	minishell->count = malloc(sizeof(t_count));
	if (!minishell->count)
	{
		perror("malloc");
		return (1);
	}
	minishell->count->pipe_count = 0;
	minishell->count->redir_in_count = 0;
	minishell->count->redir_out_count = 0;
	minishell->count->append_count = 0;
	minishell->count->heredoc_count = 0;
	return (0);
}
void	reset_counts(t_minishell *minishell)
{
	if (!minishell || !minishell->count)
		return ;
	minishell->count->pipe_count = 0;
	minishell->count->redir_in_count = 0;
	minishell->count->redir_out_count = 0;
	minishell->count->append_count = 0;
	minishell->count->heredoc_count = 0;
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	
	// Tırnak var mı kontrol et
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || 
		(str[0] == '\'' && str[len - 1] == '\'')))
	{
		result = malloc(len - 1);
		if (!result)
			return (NULL);
		i = 1;
		j = 0;
		while (i < len - 1)
		{
			result[j] = str[i];
			i++;
			j++;
		}
		result[j] = '\0';
		return (result);
	}
	return (ft_strdup(str));
}
