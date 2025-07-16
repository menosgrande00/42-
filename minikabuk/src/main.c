#include "minishell.h"

void free_env_list(t_env *list)
{
    t_env *tmp;
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

void free_token_list(t_token_list *list)
{
    t_token_list *tmp;
    while (list)
    {
        tmp = list;
        list = list->next;
        if (tmp->token)
        {
            free(tmp->token->value);
            free(tmp->token);
        }
        free(tmp);
    }
}

t_minishell	*create_minishell()
{
	t_minishell *minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
	{
		perror("malloc");
		return (NULL);
	}
	calloc_minishell(minishell);
	if (!minishell->count)
    {
		free(minishell);
	    return (NULL);
	}
	minishell->input = NULL;
	minishell->envp = malloc(sizeof(t_env));
	if (!minishell->envp)
	{
		free(minishell->count);
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

	while (1)
	{
		minishell->input = readline(get_prompt());
		if (!minishell->input)
		{
			printf("exit\n");
			break;
		}
		else if (*minishell->input)
		{
			add_history(minishell->input);
            if (tokenizer(minishell))
            {
                parse_tokens(minishell);
                execute_command(minishell);
            }
		}
		if (minishell->token_list)
		{
    		free_token_list(minishell->token_list);
    		minishell->token_list = NULL;
		}
		free(minishell->input);
	}
	if (minishell->token_list)
    	free_token_list(minishell->token_list);
	if (minishell->envp)
		free_env_list(minishell->envp);
	if (minishell->count)
		free(minishell->count);
	free(minishell);
	return (0);
}
