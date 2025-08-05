#include "minishell.h"

void	skip_redirect_tokens(t_token_list **tmp)
{
	while (*tmp)
	{
		if ((*tmp)->token->type == TOKEN_REDIRECT_IN || 
			(*tmp)->token->type == TOKEN_REDIRECT_OUT ||
			(*tmp)->token->type == TOKEN_APPEND ||
			(*tmp)->token->type == TOKEN_HEREDOC)
		{
			*tmp = (*tmp)->next;
			if (*tmp)
				*tmp = (*tmp)->next;
		}
		else if ((*tmp)->token->type == TOKEN_COMMAND || (*tmp)->token->type == TOKEN_WORD)
			*tmp = (*tmp)->next;
		else
			break;
	}
}

int	has_redirect_or_heredoc(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC
			|| tmp->token->type == TOKEN_APPEND
			|| tmp->token->type == TOKEN_REDIRECT_IN
			|| tmp->token->type == TOKEN_REDIRECT_OUT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int has_input_redirect_or_heredoc(t_minishell *minishell)
{
    t_token_list *tmp;

    tmp = minishell->token_list;
    while (tmp && tmp->token->type != TOKEN_PIPE)
    {
        if (tmp->token->type == TOKEN_HEREDOC
            || tmp->token->type == TOKEN_REDIRECT_IN)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}