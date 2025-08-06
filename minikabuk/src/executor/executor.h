#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_minishell t_minishell;
typedef struct s_token_list t_token_list;
typedef struct s_env t_env;

typedef struct s_red_files
{
	char	*input;
	char	*output;
	char	*append;
	char	*heredoc;
} t_red_files;

int     exec_child(char **cmd, t_minishell *minishell);
char	**current_token(t_token_list *tmp);

//exec_cmd.c
int     execute_command(t_minishell *minishell);
int		has_redirect_or_heredoc(t_minishell *minishell);
void	execute_in_parent(char *cmd, t_minishell *minishell);
int		has_input_redirect_or_heredoc(t_minishell *minishell);
int		has_redirect_or_heredoc(t_minishell *minishell);
int		handle_fork_and_execute(t_minishell *minishell, char **cmd, t_token_list *tmp);
int		process_single_token(t_minishell *minishell, t_token_list **tmp);
void	validate_and_execute(t_minishell *minishell, char **cmd, char *path);

//executor_utils.c
int     malloc_fd_and_pid(int ***fd, pid_t **pids, t_minishell *minishell);
int		free_for_exit(t_minishell *minishell);
int     ft_cd_util(char *current_token, char *cwd, char *new_path, t_minishell *minishell);
int		process_for_echo(t_token_list **tmp);
int		is_pipeline(t_minishell *minishell);
int     exec_child(char **cmd, t_minishell *minishell);
int 	is_valid_identifier(const char *name);
void	ft_cd_back_start(t_minishell *minishell);
char    **ft_same_tokens(t_token_list **tmp);
void	free_token_list(t_token_list *list);
void	free_env_list(t_env *list);
void	free_double(char **str);

//pipe.c
int		execute_pipe_line(t_minishell *minishell, int i);
void	execute_pipe_child(t_minishell *minishell);
void 	execute_pipe_builds(t_minishell *minishell, char **cmd);

//redirection.c
int     handle_redirect(t_minishell *minishell, t_token_list **token_list);
int     handle_heredoc(t_minishell *minishell);
char	*get_path(t_env *envp, char *cmd);
void	free_cmd_path(char **cmd_path, int i);
char	*process_env(t_minishell *minishell, char *cmd, char **cmd_path);
int     execute_redirect_child(t_minishell *minishell);
void	skip_redirect_tokens(t_token_list **tmp);
t_token_list	*skip_redirect_token(t_token_list *tmp);
int		extract_redirect_files(t_token_list *tmp, char **input_file, 
								char **output_file, char **append_file);
int		setup_all_redirection(t_minishell *ms, char *input_file);
int		count_command_tokens(t_token_list *token_list);
int		execute_external_command(char **cmd, t_minishell *minishell);

int     is_dot(char **cmd);

#endif