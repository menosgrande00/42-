#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>

typedef struct s_env{
    char *key;
    char *value;
    struct s_env *next;
}   t_env;

char    *get_prompt();
void    pre_signals();
t_env   *init_env(char **envp);

#endif