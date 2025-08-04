#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

typedef struct s_minishell t_minishell;

typedef struct s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}		t_env;

t_env	*init_env(char **envp);
void	print_envs_alphabetic(t_env *env);
t_env	*env_node(char *str);
t_env	**env_to_array(t_env *env);
char	*get_env_value(t_env *envp, char *key);
char	*extract_env_key(char *tmp, int *j);
char	*extract_env_key_double(t_minishell *minishell, int *i);

#endif