#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *input;
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	input = readline(get_prompt());
	init_env(envp);
	pre_signals();
	while (input != NULL)
	{
		input = readline(get_prompt());
		if (*input)
			add_history(input);
		free(input);
	}
	return (1);
}
