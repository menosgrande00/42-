#include "minishell.h"

t_minishell	*create_minishell()
{
	t_minishell *minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
	{
		perror("malloc");
		return (NULL);
	}
	minishell->input = NULL;
	minishell->envp = malloc(sizeof(t_env));
	if (!minishell->envp)
	{
		perror("malloc");
		free(minishell);
		return (NULL);
	}
	minishell->tokens = NULL;
	minishell->exit_status = 0;
	return (minishell);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell		*minishell;

	(void)argc;
	(void)argv;
	init_signal();
	minishell = create_minishell();
	minishell->envp = init_env(envp);
	minishell->input = "a";
	while (minishell->input != NULL)
	{
		minishell->input = readline(get_prompt());
		if (minishell->input && (*minishell->input))
		{
			add_history(minishell->input);
            if (tokenizer(minishell))
            {
                parse_tokens(minishell);
                //execute_command(minishell);
            }
		}
		t_token_list *temp = minishell->token_list;
		while (temp)
		{
			printf("Token: %u\n", temp->token->type);
			temp = temp->next;
		}
		free(minishell->input);
	}
	free(minishell);
	return (0);
}
