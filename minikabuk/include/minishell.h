#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include "parser.h"
# include "environment.h"
# include "executor.h"

typedef struct s_token_list t_token_list;
typedef struct s_env t_env;

typedef struct s_count
{
	int	pipe_count;
	int	redir_in_count;
	int	redir_out_count;
	int	append_count;
	int	heredoc_count;
}	t_count;

typedef struct s_minishell
{
	char			*input;
	t_env			*envp;
	char			**tokens;
	int				exit_status;
	t_token_list	*token_list;
	t_count			*count;
}		t_minishell;

void	ft_ctrl_c(int sig);
char	*get_prompt();
t_env	*init_env(char **envp);
void	init_signal(void);
int 	ft_strcmp(const char *s1, const char *s2);
void	calloc_minishell(t_minishell *minishell);
int		execute_command(t_minishell *minishell);
void    reset_counts(t_minishell *minishell);
void	set_ignore_signals(void);
void	set_default_signals(void);

#endif