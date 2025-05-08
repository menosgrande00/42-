#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_minishell t_minishell;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}	t_token_list;

void	parse_tokens(t_minishell *minishell);
t_token_list	*tokenizer(t_minishell *minishell);
void	add_token_to_list(t_token_list **token_list, t_token *current_token);

#endif