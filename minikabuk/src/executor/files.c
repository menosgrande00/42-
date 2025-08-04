#include "minishell.h"
//
//char *exec_files(t_minishell *minishell, t_token_list **tmp, char **cmd, char *path)
//{
//	if (cmd[0][0] == '/')
//	{
//		if (access(cmd[0], F_OK) == 0)
//			path = ft_strdup(cmd[0]);
//		else
//		{
//			exec_files(minishell, tmp, &cmd[0], path);
//        	write(2, "minishell: ", 11);
//        	write(2, cmd[0], ft_strlen(cmd[0]));
//    		write(2, ": command not found\n", 20);
//        	exit(126);
//		}
//		cmd = ft_same_tokens(tmp);
//    	execve(path, cmd, make_env_array(minishell));
//		exit(1);
//	}
//	return(0);
//}
//