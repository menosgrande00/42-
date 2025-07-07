#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_minishell t_minishell;
typedef struct s_token_list t_token_list;
typedef struct s_env t_env;

//builtin.c
int		ft_echo(char *current_token);
int		ft_env(t_minishell *minishell);
int		ft_pwd();

//builtin_2.c
int		ft_cd(t_minishell *minishell);
int		ft_export(t_minishell *minishell);
int		ft_unset(t_minishell *minishell, char *current_token);
int		ft_exit(t_minishell *minishell);

//exec_cmd_2.c
int     exec_child(char **cmd, t_minishell *minishell);
char	**current_token(t_token_list *tmp);

//exec_cmd.c
int     execute_command(t_minishell *minishell);
int		has_redirect_or_heredoc(t_minishell *minishell);
void	execute_in_parent(char *cmd, t_minishell *minishell);
char	**make_env_array(t_minishell *minishell);

//executor_utils.c
void	malloc_fd_and_pid(int ***fd, pid_t **pids, t_minishell *minishell);
int		free_for_exit(t_minishell *minishell);
int     ft_cd_util(char *current_token, char *cwd, char *new_path, t_minishell *minishell);
int		process_for_echo(t_token_list **tmp);
int		is_pipeline(t_minishell *minishell);
int     exec_child(char **cmd, t_minishell *minishell);
void	add_env(t_minishell *minishell, char *arg);
int 	is_valid_identifier(const char *name);
void	ft_cd_back_start(t_minishell *minishell);
char    **ft_same_tokens(t_token_list **tmp);
//pipe.c
int		execute_pipe_line(t_minishell *minishell, int i);
int     execute_pipe_child(t_minishell *minishell);


//redirection.c
int	    handle_redirect_or_heredoc(t_minishell *minishell, t_token_list **token_list);
char	*get_path(t_env *envp, char *cmd);
void	free_cmd_path(char **cmd_path, int i);
char	*process_env(t_minishell *minishell, char *cmd, char **cmd_path);
int     execute_redirect_herodoc_child(t_minishell *minishell);

#endif