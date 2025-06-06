#include "minishell.h"
#include <ctype.h>

static char    *get_env_value(t_minishell *minishell, char *key)
{
    t_env   *env;

    env = minishell->envp;
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return ("");
}

static long    eval_expr(char *expr)
{
    char    *p;
    long    result;
    long    value;
    char    op;

    p = expr;
    result = strtol(p, &p, 10);
    while (*p)
    {
        while (isspace(*p))
            p++;
        op = *p;
        if (!op)
            break ;
        p++;
        value = strtol(p, &p, 10);
        if (op == '+')
            result += value;
        else if (op == '-')
            result -= value;
        else if (op == '*')
            result *= value;
        else if (op == '/')
            result /= value;
        else if (op == '%')
            result %= value;
    }
    return (result);
}

int money_money(t_minishell *minishell, int *i, t_token **current_token)
{
    char    *tmp;
    char    *value;
    int     start;
    long    num;

    (*i)++; // skip $
    if (minishell->input[*i] == '?')
    {
        tmp = ft_itoa(minishell->exit_status);
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
        add_token_to_list(&minishell->token_list, *current_token);
        (*i)++;
        return (0);
    }
    else if (minishell->input[*i] == '(' && minishell->input[*i + 1] == '(')
    {
        start = *i + 2;
        *i += 2;
        while (minishell->input[*i] && !(minishell->input[*i] == ')' && minishell->input[*i + 1] == ')'))
            (*i)++;
        if (!minishell->input[*i])
            return (1);
        tmp = ft_substr(minishell->input, start, *i - start);
        if (!tmp)
            return (1);
        num = eval_expr(tmp);
        free(tmp);
        tmp = ft_itoa(num);
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
        add_token_to_list(&minishell->token_list, *current_token);
        *i += 2;
        return (0);
    }
    start = *i;
    while (minishell->input[*i] && (ft_isalnum(minishell->input[*i]) || minishell->input[*i] == '_'))
        (*i)++;
    tmp = ft_substr(minishell->input, start, *i - start);
    if (!tmp)
        return (1);
    value = ft_strdup(get_env_value(minishell, tmp));
    free(tmp);
    if (!value)
        return (1);
    *current_token = ft_calloc(sizeof(t_token), 1);
    if (!*current_token)
    {
        free(value);
        return (1);
    }
    (*current_token)->value = value;
    (*current_token)->type = TOKEN_WORD;
    add_token_to_list(&minishell->token_list, *current_token);
    return (0);
}

int double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
    char    *tmp;
    int             start;

    start = ++(*i);
    while (minishell->input[*i] && minishell->input[*i] != '"')
    {
        if (minishell->input[*i] == '$')
        {
            if (*i - start > 0)
            {
                tmp = ft_substr(minishell->input, start, (*i) - start);
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
                add_token_to_list(&minishell->token_list, *current_token);
            }
            if (money_money(minishell, i, current_token))
                return (1);
            start = *i;
            continue;
        }
        (*i)++;
    }
    if (minishell->input[*i] != '"')
    {
        ft_printf("syntax error: unclosed quote\n");
        return (1);
    }
    tmp = ft_substr(minishell->input, start, (*i) - start);
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
    add_token_to_list(&minishell->token_list, *current_token);
    (*i)++;
    return (0);
}

int     single_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
        char    *tmp;
        int             start;

        start = ++(*i);
        while (minishell->input[*i] && minishell->input[*i] != '\'')
                (*i)++;
        if (minishell->input[*i] == '\0')
        {
                ft_printf("syntax error: unclosed quote\n");
                return (1);
        }
        *current_token = ft_calloc(sizeof(t_token), 1);
        if (!*current_token)
                return (1);
        tmp = ft_substr(minishell->input, start, *i - start);
        if (!tmp)
        {
                free(*current_token);
                return (1);
        }
        (*current_token)->value = tmp;
        (*current_token)->type = TOKEN_WORD;
        add_token_to_list(&minishell->token_list, *current_token);
        (*i)++;
        return (0);
}
