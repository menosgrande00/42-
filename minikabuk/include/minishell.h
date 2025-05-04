#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}		t_env;

typedef struct s_minishell
{
	char            *input;
	t_env			*envp;
	char            **tokens;
	int             exit_status;
}		t_minishell;



void	split_input(t_minishell *minishell);
void	ft_ctrl_c(int sig);
char    *get_prompt();
t_env	*init_env(char **envp);

#endif