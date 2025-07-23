#include "minishell.h"

void remove_single_quotes_from_input(t_minishell *minishell, int j_pos, int i_pos)
{
    char *new_input;
    int len = ft_strlen(minishell->input);
    int new_len = len - 2; // İki tırnak kaldırılacak
    int k = 0;

    new_input = malloc(new_len + 1);
    if (!new_input)
        return;
    for (int idx = 0; idx < j_pos; idx++)
        new_input[k++] = minishell->input[idx];
    for (int idx = j_pos + 1; idx < i_pos; idx++)
        new_input[k++] = minishell->input[idx];
    for (int idx = i_pos + 1; idx < len; idx++)
        new_input[k++] = minishell->input[idx];
    new_input[k] = '\0';
    free(minishell->input);
    minishell->input = new_input;
}

static int	create_single_quote_token(t_minishell *minishell, int start, int i, t_token **current_token)
{
    char	*tmp;

    tmp = ft_substr(minishell->input, start, i - start);
    if (!tmp)
        return (1);
    *current_token = ft_calloc(sizeof(t_token), 1);
    if (!*current_token)
    {
        free(tmp);
        return (1);
    }
    (*current_token)->value = tmp;
    (*current_token)->type = TOKEN_WORD;
    (*current_token)->quotes = 1;
    return (0);
}

static int	handle_single_quote_merging(t_minishell *minishell, int *i, t_token **current_token, int j)
{
    if (minishell->input[j - 1] == ' ' && (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\0'))
    {
        add_token_to_list(&minishell->token_list, *current_token);
        (*i)++;
        return (0);
    }
    if (minishell->input[j - 1] != ' ')
    {
        merge_with_previous_token(minishell, current_token);
        if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
        {
            handle_after_quote_text(minishell, i, j);
            while (minishell->input[*i] != ' ' && minishell->input[*i] != '\0')
                (*i)++;
        }
    }
    else if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
    {
        remove_single_quotes_from_input(minishell, j, *i);
        *i = j - 2;
    }
    (*i)++;
    return (0);
}

static int	process_single_quote_content(t_minishell *minishell, int *i, t_token **current_token, int *start)
{
	(void)current_token;
    (void)start;
    while (minishell->input[*i] && minishell->input[*i] != '\'')
        (*i)++;
    if (minishell->input[*i] != '\'')
    {
        write(2, "syntax error: unclosed quote\n", 29);
        minishell->exit_status = 2;
        return (1);
    }
    return (0);
}

int	single_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
    int	start;
    int	j;
    int	ret;

    j = (*i);
    start = ++(*i);
    ret = process_single_quote_content(minishell, i, current_token, &start);
    if (ret != 0)
        return (ret);
    if (create_single_quote_token(minishell, start, *i, current_token))
        return (1);
    return (handle_single_quote_merging(minishell, i, current_token, j));
}