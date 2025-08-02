#include "minishell.h"

int handle_after_quote_text(t_minishell *minishell, int *i, int j)
{
    int				end_pos;
    char			*result;
    t_token_list	*last;
    int				new_tok_len;
    t_rebuild_info	info;

    result = collect_after_quot(minishell->input, *i, &end_pos);
    if (!result)
        return (1);
    append_to_last_token(minishell, result);
    last = minishell->token_list;
    while (last && last->next)
        last = last->next;
    if (last)
        new_tok_len = ft_strlen(last->token->value);
    else
        new_tok_len = 0;
    free(result);
    info.prefix_len = j;
    info.remaining_start = end_pos;
    info.new_token_len = new_tok_len;
	minishell->exit_status = rebuild_input_update_index(minishell, info, i);
    if (minishell->exit_status)
        return (1);
    return (0);
}

int	merge_with_previous_token(t_minishell *minishell, t_token **current_token)
{
	t_token_list	*last;
	char			*new_value;

	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last)
	{
		if (!ft_strcmp(last->token->value, ">") ||
            !ft_strcmp(last->token->value, "<") ||
            !ft_strcmp(last->token->value, ">>") ||
            !ft_strcmp(last->token->value, "<<"))
        {
            add_token_to_list(&minishell->token_list, *current_token);
            return (0);
        }
		new_value = ft_strjoin(last->token->value, (*current_token)->value);
		if (new_value)
		{
			free(last->token->value);
			last->token->value = new_value;
		}
		free((*current_token)->value);
		free(*current_token);
	}
	else
		add_token_to_list(&minishell->token_list, *current_token);
	return (0);
}

void remove_quotes_from_input(t_minishell *minishell, int j_pos, int i_pos)
{
    char    *new_input;
    int     len;
    int     new_len;
    int     k;
    int     idx;

    k = 0;
    len = ft_strlen(minishell->input);
    new_len = len - 2;
    new_input = malloc(new_len + 1);
    if (!new_input)
        return;
    idx = 0;
    while (idx < j_pos)
        new_input[k++] = minishell->input[idx++];
    idx = j_pos + 1;
    while (idx < i_pos)
        new_input[k++] = minishell->input[idx++];
    idx = i_pos + 1;
    while (idx < len)
        new_input[k++] = minishell->input[idx++];
    new_input[k] = '\0';
    free(minishell->input);
    minishell->input = new_input;
}
