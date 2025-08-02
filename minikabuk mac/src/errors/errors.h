#ifndef ERRORS_H
# define ERRORS_H

# define ERR_CMD_NOT_FOUND		127
# define ERR_NUM_ARG_REQ		255
# define ERR_NO_FILE			1
# define ERR_PERMISSION_DENIED	126
# define ERR_INVALID_ARG		2
# define ERR_SYNTAX				258
# define ERR_VARIABLE_DEF		1
# define ERR_PIPE_REDIR			1
# define ERR_BACKGROUND			1
# define ERR_MEMORY				1
# define ERR_FILESYSTEM			1

typedef struct s_minishell t_minishell;

int	report_error(t_minishell *minishell, const char *msg, int code);
int	report_cmd_not_found(t_minishell *minishell, const char *cmd);
int	report_num_arg_req(t_minishell *minishell, const char *cmd, int len);

#endif