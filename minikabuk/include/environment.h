#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

typedef struct s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}		t_env;

void	unset_one(t_env **env, const char *key);
void	print_envs_alphabetic(t_env *env);
t_env	*init_env(char **envp);
void	print_envs(t_env *env);
int		is_valid_key(char *key);
void export_one(t_env **env_list, const char *arg);

#endif