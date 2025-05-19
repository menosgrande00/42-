#include "minishell.h"

char    *get_prompt()
{
	char    *cwd;
	char    *prompt;
	char    *merge;

	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin("minishell@", cwd);
	merge = ft_strjoin(prompt, "$");
	return (merge);
}
