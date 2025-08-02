#include "minishell.h"

int rebuild_input_update_index(t_minishell *minishell,
	t_rebuild_info info, int *index)
{
	int rem_len;
	int total_len;
	char *new_input;
	int i;
	int j;

	rem_len = ft_strlen(&minishell->input[info.remaining_start]);
	total_len = info.prefix_len + rem_len;
	new_input = malloc(total_len + 1);
	i = 0;
	if (!new_input)
		return (1);
	while (i++ < info.prefix_len)
		new_input[i] = minishell->input[i];
	j = 0;
	while (j++ < rem_len)
		new_input[info.prefix_len + j] = minishell->input[info.remaining_start + j];
	new_input[total_len] = '\0';
	free(minishell->input);
	minishell->input = new_input;
	*index = info.prefix_len + info.new_token_len - 1;
	return (0);
}

void	append_to_last_token(t_minishell *minishell, const char *result)
{
	t_token_list	*last;
	char			*combined;

	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last)
	{
		combined = ft_strjoin(last->token->value, result);
		if (combined)
		{
			free(last->token->value);
			last->token->value = combined;
		}
	}
}

static char *handle_single_char(const char *input, int *pos_ptr, char *result)
{
	char *single; 
	char *tmp;

	single = malloc(2);
	single[0] = input[*pos_ptr];
	single[1] = '\0';
	tmp = ft_strjoin(result, single); 
	free(result);
	free(single);
	if (!tmp) 
		return (NULL);
	*pos_ptr = *pos_ptr + 1;
	return (tmp);
}

static char *handle_quoted_segment(const char *input, int *pos_ptr, char *result)
{
	int qs; 
	int qe;
	char *quoted; 
	char *tmp;

	qs = *pos_ptr;
	qe = qs + 1;
	while (input[qe] && input[qe] != '"') 
		qe++;
	if (input[qe] != '"') 
		return result;
	quoted = ft_substr(input, qs + 1, qe - qs - 1);
	if (!quoted) 
		return (result); 
	tmp = ft_strjoin(result, quoted); 
	free(result); 
	free(quoted);
	if (!tmp) 
		return (NULL); 
	*pos_ptr = qe + 1;
	return (tmp);
}

char    *collect_after_quot(const char *input, int start_idx, int *out_end_pos)
{
	int		pos;
	char	*result;

	pos = start_idx + 1;
	result = ft_strdup("");
	if (!result) 
		return (NULL);
	while (input[pos] && input[pos] != ' ')
	{
		if (input[pos] == '"')
			result = handle_quoted_segment(input, &pos, result);
		else
			result = handle_single_char(input, &pos, result);
		if (!result)
		{
			free(result); 
			return (NULL); 
		}
	}
	*out_end_pos = pos;
	return (result);
}
