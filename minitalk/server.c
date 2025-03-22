#include "minitalk.h"

void convert(int sig)
{
    static int c;
	static int bit;

    if (sig == SIGUSR2)
        c |= (1 << bit);
    
    if (bit < 7)
        bit++;
    else
    {
        ft_printf("%c", c);
        bit = 0;
        c = 0;
    }
}
int	main(int argc, char **argv)
{
	int	pid;
	(void)argv;

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
	}
	return (0);
}
