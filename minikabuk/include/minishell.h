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

typedef struct s_minishell
{
	char			*input;
	t_env			*envp;
	char			**tokens;
	int				exit_status;
	t_token_list	*token_list;
}		t_minishell;

void	split_input(t_minishell *minishell);
void	ft_ctrl_c(int sig);
char	*get_prompt();
t_env	*init_env(char **envp);
void	init_signal(void);
int 	ft_strcmp(const char *s1, const char *s2);
void	ft_ctrl_c(int sig);

#endif