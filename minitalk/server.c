#include "minitalk.h"

t_value bit;

void convert(int sig)
{
    static int c;

    if (sig == SIGUSR2)
        c |= (1 << bit.numbit);
    
    if (bit.numbit < 7)
        bit.numbit++;
    else
    {
        ft_printf("%c", c);
        bit.numbit = 0;
        c = 0;
    }
}
int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	bit.numbit = 0;
	if (argc != 1)
	{
		ft_printf("Error\n");
		return (0);
	}
	pid = getpid();
	ft_printf("%d\n", pid);
	while (argc == 1)
	{
		signal (SIGUSR1, convert);
		signal (SIGUSR2, convert);
		usleep (400);
	}
	return (0);
}
