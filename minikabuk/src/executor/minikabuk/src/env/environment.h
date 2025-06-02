#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

typedef struct s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}		t_env;

t_env	*init_env(char **envp);
void	print_envs_alphabetic(t_env *env);
t_env	*env_node(char *str);

#endif