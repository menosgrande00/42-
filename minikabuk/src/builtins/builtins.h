#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_minishell t_minishell;
typedef struct s_token_list t_token_list;
typedef struct s_env t_env;
typedef struct s_red_files t_red_files;

int	    ft_cd(t_minishell *minishell);
void	ft_cd_back_start(t_minishell *minishell);
int     ft_cd_util(char *current_token, char *cwd, char *new_path, t_minishell *minishell);

int     ft_echo(char *current_token);
int     process_for_echo(t_token_list **tmp);
int	    ft_echo_from_cmd_array(char **cmd);

int     ft_env(t_minishell *minishell);

int	    ft_exit(t_minishell *minishell);
int	    handle_quoted_args(t_minishell *minishell, char **tmp);
int	    handle_single_arg(t_minishell *minishell);

int		ft_pwd();

int		ft_export(t_minishell *minishell);
void	print_envs_alphabetic(t_env *env);

int		ft_unset(t_minishell *minishell, char *current_token);

#endif