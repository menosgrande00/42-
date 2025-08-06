#include "minishell.h"

static void heredoc_child(t_minishell *ms, char	*del, int pipe_fd)
{
	char	*line;
	int		tty_fd;

	(void)ms;
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	tty_fd = open("/dev/tty", O_RDWR);
	if (tty_fd != -1)
	{
		dup2(tty_fd, STDIN_FILENO);
		dup2(tty_fd, STDOUT_FILENO);
		close(tty_fd);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "warning: heredoc delimited by EOF\n", 35);
			close(pipe_fd);
			exit(0);
		}
		else if (ft_strcmp(line, del) == 0)
		{
			free(line);
			close(pipe_fd);
			exit(0);
		}
		ft_putstr_fd(line, pipe_fd);
		ft_putstr_fd("\n", pipe_fd);
		free(line);
	}
}

static int  setup_heredoc(t_minishell *ms, char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc_child(ms, delimiter, pipe_fd[1]);
	}
	else if(pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		init_signal();
		if ((WIFEXITED(status) && WEXITSTATUS(status) == 130))
		{
			ms->exit_status = 130;
			close(pipe_fd[0]);
			return (-1);
		}
		else if (WIFSIGNALED(status))
        {
            ms->exit_status = 128 + WTERMSIG(status);
            close(pipe_fd[0]);
            return (-1);
        }
        return (pipe_fd[0]);
	}
	else
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (0);
}

int     handle_heredoc(t_minishell *ms)
{
    t_token_list	*tmp;
    int				fd;

	fd = -1;
	tmp = ms->token_list;
	while (tmp && tmp->token->type != TOKEN_PIPE)
	{
		if (tmp->token->type == TOKEN_HEREDOC && tmp->next)
		{
			if (fd != -1)
				close(fd);
			fd = setup_heredoc(ms, tmp->next->token->value);
			if (fd == -1 || ms->exit_status == 130)
				return (1);
		}
		tmp = tmp->next;
	}
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
    return (0);
}
