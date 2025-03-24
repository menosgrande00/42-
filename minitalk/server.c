#include "minitalk.h"

void	decode_bit(int sig, char *c, int *bit)
{
	if (sig == SIGUSR1)
		*c |= 1 << *bit;
	(*bit)++;
}

void	processor(int sig)
{
	static char	c;
	static int	bit;
	static int	i;
	static int	pid;

	decode_bit(sig, &c, &bit);
	i++;
	if (bit == 8)
	{
		if (c == '\0')
		{
			printf("\nPID: \n%d\nMessage received\n", pid);
			i = 0;
			pid = 0;
		}
		else if (i < 48)
			pid = pid * 10 + (c - '0');
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	if (i >= 47)
		kill(pid, SIGUSR1);
}

int	main(void)
{
	write(1, "\n", 1);
	if (signal(SIGUSR1, processor) == SIG_ERR 
		|| signal(SIGUSR2, processor) == SIG_ERR)
	{
		printf("Error\n");
		return (0);
	}
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (1);
}
