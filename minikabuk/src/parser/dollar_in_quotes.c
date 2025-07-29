#include "minishell.h"

static int  re_build_input(t_minishell *minishell, int *i, char *value, int key_len)
{
    char *last;
    char *new_input;
    int remaining_len;
    int value_len;
    int prefix_len;
    int new_total_len;

    prefix_len = (*i);
    value_len = ft_strlen(value);
    remaining_len = ft_strlen(&minishell->input[(*i) + key_len + 1]);
    new_total_len = prefix_len + value_len + remaining_len;
    last = malloc(remaining_len + 1);
    if (!last)
        return (1);
    ft_strcpy(last, &minishell->input[(*i) + key_len + 1]);
    new_input = malloc(new_total_len + 1);
    if (!new_input)
    {
        free(last);
        return (1);
    }
    ft_strncpy(new_input, minishell->input, prefix_len);
    ft_strcpy(new_input + prefix_len, value);
    ft_strcpy(new_input + prefix_len + value_len, last);
    new_input[new_total_len] = '\0';
    free(minishell->input);
    minishell->input = new_input;
    free(last);
    (*i) += value_len - 1;
    return (0);
}

static int  set_input_path(t_minishell *minishell, int *i)
{
	char	*key;
	char	*value;
    int     len;

	key = extract_env_key_double(minishell, i);
	if (!key)
		return (1);
	value = get_env_value(minishell->envp, key);
	if (!value)
		return (1);
    len = ft_strlen(key);
	re_build_input(minishell, i, value, len);
	return (0);
}

static int  replace_input(t_minishell *minishell, int *i)
{
	char	*status;
	char	*last;
	int		len;
	int		j;

	status = ft_itoa(minishell->exit_status);
	len = *i;
	while(minishell->input[len])
		len++;
	last = malloc(len - 2);
	if (!last)
		return (1);
	j = 0;
	len = (*i) + 2;
	while (minishell->input[len])
		last[j++] = minishell->input[len++];
	last[j] = '\0';
	j = 0;
	len = *i;
	while (status[j])
		minishell->input[len++] = status[j++];
	free(status);
	(*i) += j;
	j = 0;
	while (last[j])
		minishell->input[len++] = last[j++];
	minishell->input[len] = '\0';
	return (0);
}

int	handle_dollar_in_quotes(t_minishell *minishell, int *i, int *start)
{
	int a = *start;

	(void)a;
	if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '"')
	{
		(*i)++;
		return (1);
	}
	else if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '?')
		replace_input(minishell, i);
	else if (minishell->input[*i] == '$')
		set_input_path(minishell, i);
	return (0);
}
