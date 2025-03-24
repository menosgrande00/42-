#include "minitalk.h"

volatile sig_atomic_t	g_flag;

void	pid_client_checker(int sig)
{
	(void)sig;
	if (sig == SIGUSR1)
		g_flag = 1;
}
void	send_char(int pid, char c)
{
	int bit;
	static int i;

	bit = 0;
	i = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		if (i > 111)
		{
			if (i == 112)
				usleep(3000);
			while (!g_flag)
				;
			g_flag = 0;
		}
		else
			usleep(1000);
		bit++;
		i++;
	}
	return ;
}

void	send_pid_str(char *pid_client_str, char *message, int pid)
{
	while (*pid_client_str)
	{
		send_char(pid, *pid_client_str);
		pid_client_str++;
	}
	send_char(pid, '\n');
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid, '\0');
}

int	main(int ac, char **av)
{
	int		pid;
	char	*message;
	int		pid_client;
	char	*pid_client_str;

	if (ac != 3)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	message = av[2];
	pid_client = getpid();
	printf("PID: %d\n", pid_client);
	pid_client_str = ft_itoa(pid_client);
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == 1 || pid > 4194304 || pid == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	signal(SIGUSR1, pid_client_checker);
	send_pid_str(pid_client_str, message, pid);
	free (pid_client_str);
	return (1);
}
