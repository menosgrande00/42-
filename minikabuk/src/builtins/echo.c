#include "minishell.h"

int	ft_echo(char *tok, int i)
{
	int	no_newline;
	int	j;

	no_newline = 0;
	while (tok[i] == '-' && tok[i + 1] == 'n')
	{
		j = i + 2;
		while (tok[j] == 'n')
			j++;
		if (tok[j] == ' ' || tok[j] == '\t' || tok[j] == '\0')
		{
			no_newline = 1;
			i = j;
			while (tok[i] == ' ' || tok[i] == '\t')
				i++;
		}
		else
			break;
	}
	while (tok[i])
		write(1, &tok[i++], 1);
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}

int		process_for_echo(t_token_list **tmp)
{
	char	*current;
	char	*temp;
	int		return_value;
	int		first;
	int		i;

	i = 0;
	current = ft_strdup("");
	if (!current)
			return (1);
	first = 1;
	*tmp = (*tmp)->next;
	while (*tmp && (*tmp)->token->type == TOKEN_WORD)
	{
		if (!first)
		{
			temp = ft_strjoin(current, " ");
			free(current);
	    	current = temp;
		}
	    if ((*tmp)->token->value)
    		temp = (*tmp)->token->value;
		else
    		temp = "";
		temp = ft_strjoin(current, temp);
	    free(current);
	    current = temp;
	    *tmp = (*tmp)->next;
	    first = 0;
	}
	return_value = ft_echo(current, i);
	free(current);
	return (return_value);
}

int	ft_echo_from_cmd_array(char **cmd)
{
	int	i;
	int j;
	int	no_newline;
	int	first;

	i = 1;
	no_newline = 0;
	first = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
		{
			no_newline = 1;
			i++;
		}
		else
		    break;
	}
	while (cmd[i] && !is_redirection(cmd[i]))
	{
	    if (!first)
	        write(1, " ", 1);
	    write(1, cmd[i], ft_strlen(cmd[i]));
	    first = 0;
	    i++;
	}
	if (!no_newline)
	    write(1, "\n", 1);
	return (0);
}
