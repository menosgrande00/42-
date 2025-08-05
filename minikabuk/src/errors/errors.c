# include "errors.h"
# include "minishell.h"

int	report_error(t_minishell *minishell, const char *msg, int code)
{
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	minishell->exit_status = code;
	return (code);
}

int	report_cmd_not_found(t_minishell *minishell, const char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	minishell->exit_status = ERR_CMD_NOT_FOUND;
	return (ERR_CMD_NOT_FOUND);
}

int	report_num_arg_req(t_minishell *minishell, const char *cmd, int len)
{
	write(2, "minishell: exit:", 11);
	if (cmd)
		write(2, cmd, len);
	write(2, ": numeric argument required\n", 28);
	write(2, "exit\n", 5);
	minishell->exit_status = ERR_NUM_ARG_REQ;
	return (ERR_NUM_ARG_REQ);
}
