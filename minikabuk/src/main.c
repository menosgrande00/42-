#include "minishell.h"

t_minishell	*create_minishell()
{
	t_minishell *minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
	{
		perror("malloc");
		return (NULL);
	}
	minishell->input = NULL;
	minishell->envp = malloc(sizeof(t_env));
	if (!minishell->envp)
	{
		perror("malloc");
		free(minishell);
		return (NULL);
	}
	minishell->tokens = NULL;
	minishell->exit_status = 0;
	return (minishell);
}

int main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_minishell		*minishell;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	minishell = create_minishell();
	minishell->envp = init_env(envp);
	minishell->input = "a";
	while (minishell->input != NULL)
	{
		minishell->input = readline(get_prompt());
		split_input(minishell);
		if (minishell->input && (*minishell->input))
			add_history(minishell->input);
		free(minishell->input);
	}
	return (0);
}
