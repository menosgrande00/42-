# include "errors.h"
# include "minishell.h"

int report_error(t_minishell *minishell, const char *msg, int code)
{
    if (msg)
    {
        write(STDERR_FILENO, msg, ft_strlen(msg));
        write(STDERR_FILENO, "\n", 1);
    }
    minishell->exit_status = code;
    return (code);
}

int report_cmd_not_found(t_minishell *minishell, const char *cmd)
{
    write(STDERR_FILENO, "minishell: ", 11);
    if (cmd)
        write(STDERR_FILENO, cmd, ft_strlen(cmd));
    write(STDERR_FILENO, ": command not found\n", 21);
    minishell->exit_status = ERR_CMD_NOT_FOUND;
    return (ERR_CMD_NOT_FOUND);
}

int report_num_arg_req(t_minishell *minishell, const char *cmd, int len)
{
    write(STDERR_FILENO, "minishell: exit:", 11);
    if (cmd)
        write(STDERR_FILENO, cmd, len);
    write(STDERR_FILENO, ": numeric argument required\n", 28);
    write(STDERR_FILENO, "exit\n", 5);
    minishell->exit_status = ERR_NUM_ARG_REQ;
    return (ERR_NUM_ARG_REQ);
}
