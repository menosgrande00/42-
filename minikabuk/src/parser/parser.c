#include "parser.h"

void	add_token_to_list(t_token_list **token_list, t_token *current_token)
{
	t_token_list	*new_node;
	t_token_list	*temp;

	new_node = malloc(sizeof(t_token_list));
	if (!new_node)
	{
		free(current_token->value);
		free(current_token);
		return ;
	}
	new_node->token = current_token;
	new_node->next = NULL;
	if (!*token_list)
		*token_list = new_node;
	else
	{
		temp = *token_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	count_tokens(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (tmp->token->type == TOKEN_PIPE)
			minishell->count->pipe_count++;
		else if (tmp->token->type == TOKEN_REDIRECT_IN)
			minishell->count->redir_in_count++;
		else if (tmp->token->type == TOKEN_REDIRECT_OUT)
			minishell->count->redir_out_count++;
		else if (tmp->token->type == TOKEN_APPEND)
			minishell->count->append_count++;
		else if (tmp->token->type == TOKEN_HEREDOC)
			minishell->count->heredoc_count++;
		tmp = tmp->next;
	}
}

void	compare_tokens(t_token *current_token, int *file)
{
	if (*file == 1)
	{
		current_token->type = TOKEN_FILE;
		*file = 0;
	}
	else if (ft_strcmp(current_token->value, "<") == 0)
		current_token->type = TOKEN_REDIRECT_IN;
	else if (ft_strcmp(current_token->value, ">") == 0)
		current_token->type = TOKEN_REDIRECT_OUT;
	else if (ft_strcmp(current_token->value, ">>") == 0)
		current_token->type = TOKEN_APPEND;
	else if (ft_strcmp(current_token->value, "<<") == 0)
		current_token->type = TOKEN_HEREDOC;
	else if (ft_strcmp(current_token->value, "|") == 0)
		current_token->type = TOKEN_PIPE;
	else
		current_token->type = TOKEN_WORD;
}

void    parse_tokens(t_minishell *minishell)
{
    t_token_list    *tmp;
    int             expect_command;
	int             expect_file;

	reset_counts(minishell);
    tmp = minishell->token_list;
    expect_command = 1;
	expect_file = 0;
    while (tmp)
    {
        compare_tokens(tmp->token, &expect_file);
        if (tmp->token->type == TOKEN_WORD && expect_command)
        {
			tmp->token->type = TOKEN_COMMAND;
			expect_command = 0;
		}
        if (tmp->token->type == TOKEN_REDIRECT_IN || 
            tmp->token->type == TOKEN_REDIRECT_OUT ||
            tmp->token->type == TOKEN_APPEND ||
            tmp->token->type == TOKEN_HEREDOC)
            expect_file = 1;
        else if (tmp->token->type == TOKEN_PIPE)
            expect_command = 1;
        tmp = tmp->next;
    }
    count_tokens(minishell);
}
